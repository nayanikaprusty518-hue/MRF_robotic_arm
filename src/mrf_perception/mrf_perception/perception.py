"""Simulated perception layer (guide.md sections 30-32).

This is the ONLY thing the robot talks to about objects. It abstracts the
source of detections behind a stable interface (mrf_msgs/PerceivedObjectArray).
Today it derives category from Gazebo ground truth (model name prefix) and pose
from /gazebo/model_states; tomorrow it could be swapped for YOLO/RT-DETR/DINO
without the robot noticing.

The robot never reads /gazebo/* and never talks to the object generator.
"""
import random

import rclpy
from rclpy.node import Node
from gazebo_msgs.msg import ModelStates
from geometry_msgs.msg import Vector3
from mrf_msgs.msg import PerceivedObject, PerceivedObjectArray

KNOWN = ('plastic', 'aluminum', 'cardboard')


class Perception(Node):
    def __init__(self):
        super().__init__('perception')
        self.declare_parameter('confidence_min', 0.90)
        self.declare_parameter('confidence_max', 0.99)
        self.cmin = self.get_parameter('confidence_min').value
        self.cmax = self.get_parameter('confidence_max').value

        self.last = {}          # name -> (x, y, z, t)
        self.confidence = {}    # name -> stable per-object confidence

        self.pub = self.create_publisher(PerceivedObjectArray, '/mrf/perception/objects', 10)
        self.create_subscription(ModelStates, '/gazebo/model_states', self.cb, 10)
        self.get_logger().info('Perception layer up (ground-truth mode).')

    def cb(self, msg):
        now = self.get_clock().now()
        t = now.nanoseconds * 1e-9
        out = PerceivedObjectArray()
        out.header.stamp = now.to_msg()
        out.header.frame_id = 'world'

        seen = set()
        for name, pose in zip(msg.name, msg.pose):
            cat = name.split('__')[0]
            if cat not in KNOWN or '__obj_' not in name:
                continue
            seen.add(name)

            px, py, pz = pose.position.x, pose.position.y, pose.position.z
            # velocity via finite difference of successive poses
            vx = vy = vz = 0.0
            if name in self.last:
                lx, ly, lz, lt = self.last[name]
                dt = t - lt
                if dt > 1e-3:
                    vx, vy, vz = (px - lx) / dt, (py - ly) / dt, (pz - lz) / dt
            self.last[name] = (px, py, pz, t)

            if name not in self.confidence:
                self.confidence[name] = random.uniform(self.cmin, self.cmax)

            o = PerceivedObject()
            o.object_id = name
            o.category = cat
            o.pose = pose
            o.velocity = Vector3(x=vx, y=vy, z=vz)
            o.confidence = self.confidence[name]
            o.stamp = out.header.stamp
            out.objects.append(o)

        # forget objects that disappeared
        for gone in set(self.last) - seen:
            self.last.pop(gone, None)
            self.confidence.pop(gone, None)

        self.pub.publish(out)


def main():
    rclpy.init()
    node = Perception()
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
