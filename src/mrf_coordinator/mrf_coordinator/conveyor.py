"""Conveyor controller.

Per guide.md section 33 the belt NEVER stops. Valid states are only
RUNNING_FAST / RUNNING_MEDIUM / RUNNING_SLOW. This node owns the belt speed,
publishes it, and offers a service to change state (but never to STOP).
"""
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64, String
from std_srvs.srv import Trigger

SPEEDS = {
    'RUNNING_FAST': 0.18,
    'RUNNING_MEDIUM': 0.10,
    'RUNNING_SLOW': 0.05,
}


class Conveyor(Node):
    def __init__(self):
        super().__init__('conveyor')
        self.declare_parameter('state', 'RUNNING_MEDIUM')
        state = self.get_parameter('state').value
        if state not in SPEEDS:
            state = 'RUNNING_MEDIUM'
        self.state = state

        self.speed_pub = self.create_publisher(Float64, '/mrf/conveyor/speed', 10)
        self.state_pub = self.create_publisher(String, '/mrf/conveyor/state', 10)
        self.create_service(Trigger, '/mrf/conveyor/cycle_speed', self.cycle_cb)
        self.create_timer(0.2, self.publish)
        self.get_logger().info(f'Conveyor running, state={self.state} '
                               f'({SPEEDS[self.state]:.2f} m/s). Belt will never stop.')

    def publish(self):
        self.speed_pub.publish(Float64(data=SPEEDS[self.state]))
        self.state_pub.publish(String(data=self.state))

    def cycle_cb(self, _req, resp):
        order = list(SPEEDS.keys())
        self.state = order[(order.index(self.state) + 1) % len(order)]
        resp.success = True
        resp.message = self.state
        self.get_logger().info(f'Conveyor state -> {self.state}')
        return resp


def main():
    rclpy.init()
    node = Conveyor()
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
