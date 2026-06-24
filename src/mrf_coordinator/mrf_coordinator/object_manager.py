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

# category -> (sdf-shape, rgba, half_height, mass)
CATEGORIES = {
    'plastic':  ('cylinder', (0.1, 0.8, 0.2, 1), 0.06, 0.05),   # green bottle
    'aluminum': ('box',      (0.6, 0.6, 0.62, 1), 0.035, 0.08),  # grey can/cube
    'cardboard': ('box',     (0.72, 0.55, 0.3, 1), 0.045, 0.04),  # tan box (decoy)
}

BELT_Y = -0.55
BELT_TOP_Z = 0.85
X_SPAWN = -1.40
X_EXIT = 1.45


def euler_to_quat(yaw):
    import math
    return (0.0, 0.0, math.sin(yaw / 2.0), math.cos(yaw / 2.0))


def make_sdf(name, cat):
    shape, rgba, half, mass = CATEGORIES[cat]
    r, g, b, a = rgba
    if shape == 'cylinder':
        geom = f'<cylinder><radius>0.03</radius><length>{half*2:.3f}</length></cylinder>'
    else:
        s = half * 2
        geom = f'<box><size>{s:.3f} {s:.3f} {s:.3f}</size></box>'
    return f"""<?xml version='1.0'?>
<sdf version='1.6'>
  <model name='{name}'>
    <link name='link'>
      <inertial><mass>{mass}</mass>
        <inertia><ixx>1e-4</ixx><iyy>1e-4</iyy><izz>1e-4</izz>
                 <ixy>0</ixy><ixz>0</ixz><iyz>0</iyz></inertia>
      </inertial>
      <visual name='v'><geometry>{geom}</geometry>
        <material><ambient>{r} {g} {b} {a}</ambient><diffuse>{r} {g} {b} {a}</diffuse></material>
      </visual>
      <collision name='c'><geometry>{geom}</geometry></collision>
    </link>
  </model>
</sdf>"""


class ObjectManager(Node):
    def __init__(self):
        super().__init__('object_manager')
        self.declare_parameter('spawn_period', 4.0)
        self.declare_parameter('category_weights', [0.6, 0.25, 0.15])  # plastic/alu/card
        self.declare_parameter('y_jitter', 0.12)
        self.declare_parameter('max_objects', 10)

        self.spawn_period = self.get_parameter('spawn_period').value
        self.weights = self.get_parameter('category_weights').value
        self.y_jitter = self.get_parameter('y_jitter').value
        self.max_objects = self.get_parameter('max_objects').value

        self.belt_speed = 0.10
        self.declare_parameter('reject_bin_x', 1.80)
        self.declare_parameter('reject_bin_y', -0.55)
        self.reject_xy = (self.get_parameter('reject_bin_x').value,
                          self.get_parameter('reject_bin_y').value)

        self.objects = {}     # name -> {'cat','half'}  (only belt-borne ones)
        self.claimed = set()  # names the robot now owns
        self.counter = 0
        self.n_spawned = 0
        self.n_rejected = 0       # reached belt end -> dropped in reject bin
        self.reject_count = 0
        self.reject_slots = {}    # FIFO-recycled grid slots in the reject bin

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
        half = CATEGORIES[cat][2]
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
                # not recovered by the arms -> drops into the reject bin at the
                # end of the belt (instead of being deleted/lost)
                self.collect_reject(name)
                self.objects.pop(name, None)
                self.n_rejected += 1
                self.get_logger().info(f'{name} reached belt end -> reject bin')
                continue
            self.set_pose(name, o['x'], o['y'], o['z'])

    def collect_reject(self, name):
        rx, ry = self.reject_xy
        slot = self.reject_count % 9
        self.reject_count += 1
        gx = (slot % 3 - 1) * 0.12
        gy = (slot // 3 - 1) * 0.12
        old = self.reject_slots.get(slot)
        if old:
            self.delete(old)
        self.reject_slots[slot] = name
        self.set_pose(name, rx + gx, ry + gy, 0.10)

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
               f'claimed={len(self.claimed)} rejected={self.n_rejected}')
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
