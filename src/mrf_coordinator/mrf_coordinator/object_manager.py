"""Object generator + conveyor motion + lifecycle (guide.md sections 28-31, 33, 38).

Responsibilities:
  * Spawn objects on the belt with RANDOM placement (offset, rotated, varied
    spacing) -- NOT in tidy aligned rows.
  * Assign a GROUND-TRUTH category at creation time (the model name encodes it,
    e.g. "plastic__obj_007"); the simulated perception layer reads this back as
    if it came from a detector.
  * Continuously advance objects along +X at the live belt speed. The belt
    never stops.
  * Objects that leave the workspace are deleted and counted as MISSED.
  * Objects "claimed" by the robot (announced on /mrf/coordinator/claimed) are
    no longer advanced -- the coordinator owns them after that.

This node deliberately knows NOTHING about the robot; it only emits world state.
"""
import random

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64, String
from gazebo_msgs.srv import SpawnEntity, DeleteEntity, SetEntityState
from gazebo_msgs.msg import EntityState

# Four realistic recyclable types, built from several primitives around the
# model origin (= grasp point). Each part: geometry + material.
#   geometry g: ('cyl', radius, length, z) | ('box', sx, sy, sz, z)
#   material m: {'script': 'MRF/...'}  (textured)  OR
#               {'rgba': (r,g,b), 'transp': 0..1, 'spec': '<ogre specular>'}
#   col=True marks the part that carries collision (the main body).
# 'half' = body half-height (sets the spawn rest height).
GLASS = '0.95 0.95 0.95 1 90'      # very glossy
CLEAR = '0.8 0.8 0.8 1 60'
METAL = '0.9 0.9 0.9 1 80'

CATEGORIES = {
    # clear PET water bottle: translucent body + shoulder/neck, blue cap, label band
    'plastic': dict(half=0.055, mass=0.04, parts=[
        dict(g=('cyl', 0.032, 0.11, 0.0),    m=dict(rgba=(0.72, 0.86, 0.96), transp=0.5, spec=CLEAR), col=True),
        dict(g=('cyl', 0.015, 0.035, 0.072), m=dict(rgba=(0.72, 0.86, 0.96), transp=0.5, spec=CLEAR)),
        dict(g=('cyl', 0.017, 0.020, 0.097), m=dict(rgba=(0.10, 0.30, 0.70))),                 # cap
        dict(g=('cyl', 0.0335, 0.05, -0.005), m=dict(script='MRF/BottleLabel')),               # label band
    ]),
    # aluminium soda can: wrapped label + silver top/bottom rims
    'metal': dict(half=0.0475, mass=0.06, parts=[
        dict(g=('cyl', 0.033, 0.095, 0.0),  m=dict(script='MRF/CanLabel'), col=True),
        dict(g=('cyl', 0.030, 0.008, 0.050), m=dict(rgba=(0.82, 0.82, 0.85), spec=METAL)),
        dict(g=('cyl', 0.030, 0.008, -0.050), m=dict(rgba=(0.82, 0.82, 0.85), spec=METAL)),
    ]),
    # green glass bottle: glossy translucent body + neck, dark cap, paper label
    'glass': dict(half=0.065, mass=0.10, parts=[
        dict(g=('cyl', 0.030, 0.13, 0.0),   m=dict(rgba=(0.10, 0.45, 0.20), transp=0.4, spec=GLASS), col=True),
        dict(g=('cyl', 0.013, 0.05, 0.090), m=dict(rgba=(0.10, 0.45, 0.20), transp=0.4, spec=GLASS)),
        dict(g=('cyl', 0.015, 0.015, 0.122), m=dict(rgba=(0.15, 0.15, 0.15))),                  # cap
        dict(g=('cyl', 0.0315, 0.04, -0.010), m=dict(script='MRF/GlassLabel')),                 # label
    ]),
    # kraft paper carton
    'paper': dict(half=0.0375, mass=0.03, parts=[
        dict(g=('box', 0.085, 0.065, 0.075, 0.0), m=dict(script='MRF/Cardboard'), col=True),
    ]),
}

BELT_Y = -0.55
BELT_TOP_Z = 0.85
X_SPAWN = -1.40
X_EXIT = 1.45


def euler_to_quat(yaw):
    import math
    return (0.0, 0.0, math.sin(yaw / 2.0), math.cos(yaw / 2.0))


def _geom(g):
    if g[0] == 'cyl':
        _, radius, length, z = g
        return z, f'<cylinder><radius>{radius:.4f}</radius><length>{length:.4f}</length></cylinder>'
    _, sx, sy, sz, z = g
    return z, f'<box><size>{sx:.4f} {sy:.4f} {sz:.4f}</size></box>'


def _material(m):
    if 'script' in m:
        return (f"""<material><script>
          <uri>model://recyclables/materials/scripts</uri>
          <uri>model://recyclables/materials/textures</uri>
          <name>{m['script']}</name></script></material>""")
    r, g, b = m['rgba']
    spec = m.get('spec', '0.1 0.1 0.1 1 1')
    return (f"<material><ambient>{r} {g} {b} 1</ambient><diffuse>{r} {g} {b} 1</diffuse>"
            f"<specular>{spec}</specular></material>")


def make_sdf(name, cat):
    spec = CATEGORIES[cat]
    elems = []
    for i, part in enumerate(spec['parts']):
        z, geom = _geom(part['g'])
        m = part['m']
        transp = m.get('transp', 0.0)
        elems.append(f"""      <visual name='v{i}'>
        <pose>0 0 {z:.4f} 0 0 0</pose>
        <geometry>{geom}</geometry>
        <transparency>{transp}</transparency>
        {_material(m)}
      </visual>""")
        if part.get('col'):
            elems.append(f"""      <collision name='c{i}'>
        <pose>0 0 {z:.4f} 0 0 0</pose>
        <geometry>{geom}</geometry>
      </collision>""")
    return f"""<?xml version='1.0'?>
<sdf version='1.6'>
  <model name='{name}'>
    <link name='link'>
      <inertial><mass>{spec['mass']}</mass>
        <inertia><ixx>1e-4</ixx><iyy>1e-4</iyy><izz>1e-4</izz>
                 <ixy>0</ixy><ixz>0</ixz><iyz>0</iyz></inertia>
      </inertial>
{chr(10).join(elems)}
    </link>
  </model>
</sdf>"""


class ObjectManager(Node):
    def __init__(self):
        super().__init__('object_manager')
        self.declare_parameter('spawn_period', 4.0)
        # plastic / metal / glass / paper
        self.declare_parameter('category_weights', [0.25, 0.25, 0.25, 0.25])
        self.declare_parameter('y_jitter', 0.12)
        self.declare_parameter('max_objects', 10)

        self.spawn_period = self.get_parameter('spawn_period').value
        self.weights = self.get_parameter('category_weights').value
        self.y_jitter = self.get_parameter('y_jitter').value
        self.max_objects = self.get_parameter('max_objects').value

        self.belt_speed = 0.10

        self.objects = {}     # name -> {'cat','half'}  (only belt-borne ones)
        self.claimed = set()  # names the robot now owns
        self.counter = 0
        self.n_spawned = 0
        self.n_missed = 0         # left the workspace unpicked

        self.spawn_cli = self.create_client(SpawnEntity, '/spawn_entity')
        self.del_cli = self.create_client(DeleteEntity, '/delete_entity')
        self.state_cli = self.create_client(SetEntityState, '/gazebo/set_entity_state')

        self.create_subscription(Float64, '/mrf/conveyor/speed', self.speed_cb, 10)
        self.create_subscription(String, '/mrf/coordinator/claimed', self.claim_cb, 10)
        self.create_subscription(String, '/mrf/coordinator/released', self.release_cb, 10)
        self.stats_pub = self.create_publisher(String, '/mrf/objects/stats', 10)

        self.get_logger().info('Object manager waiting for Gazebo spawn service...')
        self.spawn_cli.wait_for_service()
        self.state_cli.wait_for_service()
        self.get_logger().info('Gazebo services up. Generating objects.')

        self.create_timer(self.spawn_period, self.spawn_one)
        self.create_timer(1.0 / 15.0, self.advance)
        self.create_timer(2.0, self.publish_stats)

    # ---- callbacks ----
    def speed_cb(self, msg):
        self.belt_speed = msg.data

    def claim_cb(self, msg):
        # robot took ownership: stop advancing / tracking it on the belt
        self.claimed.add(msg.data)
        self.objects.pop(msg.data, None)

    def release_cb(self, msg):
        # object fully consumed (dropped in bin); forget it
        self.claimed.discard(msg.data)

    # ---- generation ----
    def spawn_one(self):
        if len(self.objects) >= self.max_objects:
            return
        cats = list(CATEGORIES.keys())
        cat = random.choices(cats, weights=self.weights[:len(cats)])[0]
        half = CATEGORIES[cat]['half']
        self.counter += 1
        name = f'{cat}__obj_{self.counter:03d}'

        y = BELT_Y + random.uniform(-self.y_jitter, self.y_jitter)
        x = X_SPAWN + random.uniform(-0.05, 0.05)
        z = BELT_TOP_Z + half + 0.005
        yaw = random.uniform(-3.14159, 3.14159)
        qx, qy, qz, qw = euler_to_quat(yaw)

        req = SpawnEntity.Request()
        req.name = name
        req.xml = make_sdf(name, cat)
        req.initial_pose.position.x = x
        req.initial_pose.position.y = y
        req.initial_pose.position.z = z
        req.initial_pose.orientation.x = qx
        req.initial_pose.orientation.y = qy
        req.initial_pose.orientation.z = qz
        req.initial_pose.orientation.w = qw
        fut = self.spawn_cli.call_async(req)
        fut.add_done_callback(lambda f, n=name: self._mark_ready(n))

        self.objects[name] = {'cat': cat, 'half': half, 'x': x, 'y': y, 'z': z,
                              'ready': False}
        self.n_spawned += 1
        self.get_logger().info(f'Spawned {name} (category={cat}) at '
                               f'x={x:.2f} y={y:.2f} yaw={yaw:.2f}')

    def _mark_ready(self, name):
        if name in self.objects:
            self.objects[name]['ready'] = True

    # ---- belt motion + miss policy ----
    def advance(self):
        dt = 1.0 / 15.0
        for name in list(self.objects.keys()):
            o = self.objects[name]
            if not o.get('ready'):
                continue
            o['x'] += self.belt_speed * dt
            if o['x'] > X_EXIT:
                # left the workspace unpicked -> removed and counted as missed
                self.delete(name)
                self.objects.pop(name, None)
                self.n_missed += 1
                self.get_logger().info(f'{name} left workspace -> MISSED')
                continue
            self.set_pose(name, o['x'], o['y'], o['z'])

    def set_pose(self, name, x, y, z):
        req = SetEntityState.Request()
        st = EntityState()
        st.name = name
        st.pose.position.x = x
        st.pose.position.y = y
        st.pose.position.z = z
        st.pose.orientation.w = 1.0
        st.reference_frame = 'world'
        req.state = st
        self.state_cli.call_async(req)

    def delete(self, name):
        req = DeleteEntity.Request()
        req.name = name
        self.del_cli.call_async(req)

    def publish_stats(self):
        msg = (f'spawned={self.n_spawned} on_belt={len(self.objects)} '
               f'claimed={len(self.claimed)} missed={self.n_missed}')
        self.stats_pub.publish(String(data=msg))


def main():
    rclpy.init()
    node = ObjectManager()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
