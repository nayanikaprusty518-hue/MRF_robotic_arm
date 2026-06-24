"""Task scheduler + pick-and-place executor (guide.md sections 34-40).

The robot is a *recovery agent*: it consumes the perception interface, selects
the best target-category object inside its work envelope, and recovers it into
the matching bin. It does NOT try to pick everything, and the belt never stops.

Pipeline:  perception -> scheduler (priority + work envelope) -> FSM -> arm

Grasping is kinematic: once a pick is committed the object is "claimed" (the
object_manager stops moving it) and the coordinator slaves the object's pose to
the live TCP until it is released over the bin. This is robust in Gazebo Classic
where physical form-closure grasping is unreliable.
"""
import math
import random

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from gazebo_msgs.srv import SetEntityState, DeleteEntity
from gazebo_msgs.msg import EntityState
from mrf_msgs.msg import PerceivedObjectArray

from mrf_coordinator import ik

GRIP_OPEN = 0.0       # claw fingers splayed out
GRIP_CLOSED = 0.9     # claw fingers curled in (revolute knuckles)
ARM_J = ['joint1', 'joint2', 'joint3', 'joint4', 'joint5', 'joint6']
GRIP_J = ['finger1_joint', 'finger2_joint', 'finger3_joint']


def yaw_of(q):
    # yaw from a quaternion (z-w dominant assumed, but compute properly)
    siny = 2.0 * (q.w * q.z + q.x * q.y)
    cosy = 1.0 - 2.0 * (q.y * q.y + q.z * q.z)
    return math.atan2(siny, cosy)


class Coordinator(Node):
    def __init__(self):
        super().__init__('coordinator')
        # identity / wiring (one instance per arm)
        self.declare_parameter('arm_name', 'arm1')
        self.declare_parameter('joint_prefix', 'a1_')
        self.declare_parameter('arm_topic', '/arm1_controller/joint_trajectory')
        self.declare_parameter('grip_topic', '/gripper1_controller/joint_trajectory')
        # which materials this arm recovers
        self.declare_parameter('target_categories', ['plastic'])
        # arm mount pose in the world (matches the URDF world_joint)
        self.declare_parameter('base_x', 0.0)
        self.declare_parameter('base_y', 0.0)
        self.declare_parameter('base_z', 0.80)
        self.declare_parameter('base_yaw', 0.0)
        # pick point (world): hover over the belt at this x; belt centre y
        self.declare_parameter('pick_x', 0.0)
        self.declare_parameter('belt_y', -0.55)
        self.declare_parameter('belt_half', 0.16)   # y half-width of grab band
        self.declare_parameter('catch_back', 0.06)  # grab window before pick_x
        self.declare_parameter('catch_ahead', 0.18) # ... and after
        # bin (world) this arm drops into
        self.declare_parameter('bin_x', -0.28)
        self.declare_parameter('bin_y', 0.55)

        self.arm_name = self.get_parameter('arm_name').value
        self.jp = self.get_parameter('joint_prefix').value
        self.targets = [c for c in self.get_parameter('target_categories').value if c] or ['plastic']
        self.bx = self.get_parameter('base_x').value
        self.by = self.get_parameter('base_y').value
        self.bz = self.get_parameter('base_z').value
        self.byaw = self.get_parameter('base_yaw').value
        self.pick_x = self.get_parameter('pick_x').value
        self.belt_y = self.get_parameter('belt_y').value
        self.belt_half = self.get_parameter('belt_half').value
        self.catch_back = self.get_parameter('catch_back').value
        self.catch_ahead = self.get_parameter('catch_ahead').value
        self.bin_xy = (self.get_parameter('bin_x').value, self.get_parameter('bin_y').value)

        self.arm_joints = [self.jp + j for j in ARM_J]
        self.grip_joints = [self.jp + j for j in GRIP_J]

        # planned poses (joint vectors) for the active pick
        self.plan = None
        self.active = None
        self.carrying = False
        self.state = 'INIT'
        self.phase_deadline = 0.0
        self.latest = []
        self.cur_q = {}
        self.n_recovered = 0
        self.n_ignored_seen = set()
        self.bin_slots = {}
        self.bin_count = 0

        self.arm_pub = self.create_publisher(
            JointTrajectory, self.get_parameter('arm_topic').value, 10)
        self.grip_pub = self.create_publisher(
            JointTrajectory, self.get_parameter('grip_topic').value, 10)
        # claim / release are SHARED so the object_manager sees both arms
        self.claim_pub = self.create_publisher(String, '/mrf/coordinator/claimed', 10)
        self.release_pub = self.create_publisher(String, '/mrf/coordinator/released', 10)
        self.state_pub = self.create_publisher(String, f'/mrf/{self.arm_name}/state', 10)
        self.stats_pub = self.create_publisher(String, f'/mrf/{self.arm_name}/stats', 10)

        self.set_cli = self.create_client(SetEntityState, '/gazebo/set_entity_state')
        self.del_cli = self.create_client(DeleteEntity, '/delete_entity')

        self.create_subscription(PerceivedObjectArray, '/mrf/perception/objects', self.perc_cb, 10)
        self.create_subscription(JointState, '/joint_states', self.js_cb, 10)

        # hover pose above the pick point (computed in this arm's base frame)
        hover = self.world_to_base([self.pick_x, self.belt_y, self.bz + 0.30])
        self.home_q = ik.ik_topdown(hover, yaw=0.0) or [0, 0.4, 0.6, 0, 0.9, 0]

        self.create_timer(0.05, self.tick)
        self.create_timer(1.0, self.publish_stats)
        self.get_logger().info(f'[{self.arm_name}] up. Targets={self.targets} '
                               f'pick_x={self.pick_x} bin={self.bin_xy}. Belt never stops.')

    # ---------- world <-> base transforms (arm mounted upright, yaw only) ----------
    def world_to_base(self, P):
        dx, dy, dz = P[0] - self.bx, P[1] - self.by, P[2] - self.bz
        c, s = math.cos(self.byaw), math.sin(self.byaw)
        return [c * dx + s * dy, -s * dx + c * dy, dz]

    def base_to_world(self, p):
        c, s = math.cos(self.byaw), math.sin(self.byaw)
        return [self.bx + c * p[0] - s * p[1], self.by + s * p[0] + c * p[1], self.bz + p[2]]

    # ---------- inputs ----------
    def perc_cb(self, msg):
        self.latest = list(msg.objects)

    def js_cb(self, msg):
        for n, p in zip(msg.name, msg.position):
            self.cur_q[n] = p
        if self.carrying and self.active:
            t = self.now()
            if t - getattr(self, '_last_slave', 0.0) > 0.04:   # ~25 Hz
                self._last_slave = t
                self.slave_object_to_tcp()

    def now(self):
        return self.get_clock().now().nanoseconds * 1e-9

    # ---------- helpers ----------
    def send_arm(self, q, dur):
        jt = JointTrajectory()
        jt.joint_names = self.arm_joints
        pt = JointTrajectoryPoint()
        pt.positions = [float(v) for v in q]
        pt.time_from_start.sec = int(dur)
        pt.time_from_start.nanosec = int((dur - int(dur)) * 1e9)
        jt.points.append(pt)
        self.arm_pub.publish(jt)

    def send_grip(self, val, dur=0.5):
        jt = JointTrajectory()
        jt.joint_names = self.grip_joints
        pt = JointTrajectoryPoint()
        pt.positions = [val] * len(self.grip_joints)
        pt.time_from_start.sec = int(dur)
        pt.time_from_start.nanosec = int((dur - int(dur)) * 1e9)
        jt.points.append(pt)
        self.grip_pub.publish(jt)

    def tcp_world(self):
        q = [self.cur_q.get(j, 0.0) for j in self.arm_joints]
        pos, _, _, _ = ik.fk(q)
        return self.base_to_world([pos[0], pos[1], pos[2]])

    def slave_object_to_tcp(self):
        x, y, z = self.tcp_world()
        # sanity: never teleport a carried object outside the cell (guards
        # against a transient bad FK flinging the object across the world)
        if abs(x) > 1.5 or abs(y) > 2.0 or z < 0.3 or z > 2.0:
            return
        req = SetEntityState.Request()
        st = EntityState()
        st.name = self.active
        st.pose.position.x = x
        st.pose.position.y = y
        st.pose.position.z = z
        st.pose.orientation.w = 1.0
        st.reference_frame = 'world'
        req.state = st
        self.set_cli.call_async(req)

    def place_object(self, x, y, z):
        req = SetEntityState.Request()
        st = EntityState()
        st.name = self.active
        st.pose.position.x = x
        st.pose.position.y = y
        st.pose.position.z = z
        st.pose.orientation.w = 1.0
        st.reference_frame = 'world'
        req.state = st
        self.set_cli.call_async(req)

    def store_in_bin(self, name):
        """Place a recovered object in a tidy single-layer 3x3 grid inside the
        bin. Slots are recycled FIFO (oldest deleted) so the bin never piles up
        and ejects objects via overlap."""
        binx, biny = self.bin_xy
        slot = self.bin_count % 9
        self.bin_count += 1
        gx = (slot % 3 - 1) * 0.10
        gy = (slot // 3 - 1) * 0.10
        old = self.bin_slots.get(slot)
        if old:
            req = DeleteEntity.Request(); req.name = old
            self.del_cli.call_async(req)
        self.bin_slots[slot] = name
        self.place_object(binx + gx, biny + gy, 0.10)   # rest on bin floor, no overlap

    # ---------- selection (sections 34-37, 39) ----------
    def plan_pick(self, obj):
        """Return joint vectors for each phase (computed in this arm's base
        frame from world poses), or None if infeasible."""
        wx, wy, wz = obj.pose.position.x, obj.pose.position.y, obj.pose.position.z
        binx, biny = self.bin_xy
        grasp = self.world_to_base([wx, wy, wz])
        hover = self.world_to_base([wx, wy, self.bz + 0.30])
        binp = self.world_to_base([binx, biny, self.bz + 0.20])
        plan = {
            'grasp': ik.ik_topdown(grasp, 0.0),
            'lift':  ik.ik_topdown(hover, 0.0),
            'bin':   ik.ik_topdown(binp, 0.0),
        }
        if any(v is None for v in plan.values()):
            return None
        # take the SHORT way around for the base joint: unwrap the bin's q1 to
        # be within +/-pi of the lift pose (avoids a ~285 deg swing when the bin
        # sits near the -X axis where q1 = +/-pi).
        ref = plan['lift'][0]
        q1 = plan['bin'][0]
        plan['bin'][0] = q1 + 2 * math.pi * round((ref - q1) / (2 * math.pi))
        return plan

    def select(self):
        """Pick the best target object that is arriving directly under the
        hovering arm. The belt keeps running; we only commit (claim) once the
        object is in the grab window, so nothing is frozen waiting far away."""
        best = None
        best_key = None
        for o in self.latest:
            if o.category not in self.targets:
                if o.object_id not in self.n_ignored_seen:
                    self.n_ignored_seen.add(o.object_id)
                continue
            x, y = o.pose.position.x, o.pose.position.y
            # grab window: object has just reached the pick point under the arm
            if not (self.pick_x - self.catch_back <= x <= self.pick_x + self.catch_ahead):
                continue
            if abs(y - self.belt_y) > self.belt_half:
                continue
            plan = self.plan_pick(o)
            if plan is None:
                continue
            # priority: closest to the pick point, then highest confidence
            key = (abs(x - self.pick_x), -o.confidence)
            if best_key is None or key < best_key:
                best_key, best, best_plan = key, o, plan
        if best is None:
            return None
        return best, best_plan

    # ---------- FSM ----------
    def enter(self, state, dur):
        self.state = state
        self.phase_deadline = self.now() + dur

    def tick(self):
        self.state_pub.publish(String(data=self.state))

        if self.state == 'INIT':
            self.send_arm(self.home_q, 2.0)
            self.send_grip(GRIP_OPEN, 1.0)
            self.enter('IDLE', 2.5)
            return

        # IDLE: arm hovers over the pick point and scans every tick (not gated
        # by a deadline) so it can grab an object the instant it arrives.
        if self.state == 'IDLE':
            if self.now() < self.phase_deadline:
                return
            sel = self.select()
            if sel is None:
                return
            obj, plan = sel
            self.active = obj.object_id
            self.plan = plan
            self.claim_pub.publish(String(data=self.active))  # robot owns it now
            self.get_logger().info(f'[{self.arm_name}] intercepting {self.active} '
                                   f'({obj.category}) at x={obj.pose.position.x:.2f}')
            self.send_arm(plan['grasp'], 0.7)
            self.send_grip(GRIP_OPEN, 0.3)
            self.enter('DESCEND', 0.8)
            return

        if self.now() < self.phase_deadline:
            return

        if self.state == 'DESCEND':
            self.send_grip(GRIP_CLOSED, 0.3)
            self.carrying = True
            self.enter('GRASP', 0.45)

        elif self.state == 'GRASP':
            self.send_arm(self.plan['lift'], 0.6)
            self.enter('LIFT', 0.7)

        elif self.state == 'LIFT':
            self.send_arm(self.plan['bin'], 1.0)
            self.enter('TO_BIN', 1.15)

        elif self.state == 'TO_BIN':
            self.send_grip(GRIP_OPEN, 0.5)
            self.store_in_bin(self.active)
            self.carrying = False
            self.release_pub.publish(String(data=self.active))
            self.n_recovered += 1
            self.get_logger().info(f'[{self.arm_name}] recovered {self.active} '
                                   f'(total {self.n_recovered})')
            self.active = None
            self.plan = None
            self.enter('RELEASE', 0.4)

        elif self.state == 'RELEASE':
            self.send_arm(self.home_q, 0.9)
            self.enter('IDLE', 1.0)

    def publish_stats(self):
        self.stats_pub.publish(String(
            data=f'state={self.state} recovered={self.n_recovered} '
                 f'targets={self.targets} ignored_seen={len(self.n_ignored_seen)}'))


def main():
    rclpy.init()
    node = Coordinator()
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
