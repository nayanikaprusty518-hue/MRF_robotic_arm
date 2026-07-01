"""Top-level launch for the MRF sorting simulation.

Brings up: Gazebo + world, the robot (URDF + ros2_control), the controllers,
the conveyor, the object generator, the simulated perception layer and the
coordinator.

Args:
  mode:=single   recover only plastic            (guide.md section 35, default)
  mode:=dual     recover plastic AND aluminum     (guide.md section 36)
  gui:=true/false   run the Gazebo client GUI
"""
import os
import re
import subprocess

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, IncludeLaunchDescription,
                            OpaqueFunction, TimerAction)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def _clean_urdf(xacro_file):
    """Run xacro and sanitise the result so it is safe both as a robot_description
    topic value and as the YAML parameter override that gazebo_ros2_control feeds
    to the controller_manager (XML declaration / comments / newlines otherwise
    abort controller_manager startup on Humble)."""
    urdf = subprocess.check_output(['xacro', xacro_file]).decode()
    urdf = re.sub(r'<\?xml[^>]*\?>', '', urdf)        # drop XML declaration
    urdf = re.sub(r'<!--.*?-->', '', urdf, flags=re.S)  # drop comments
    urdf = re.sub(r'\s+', ' ', urdf).strip()          # collapse whitespace
    return urdf


def launch_setup(context, *args, **kwargs):
    desc_share = get_package_share_directory('mrf_description')
    gz_share = get_package_share_directory('mrf_gazebo')
    gazebo_ros_share = get_package_share_directory('gazebo_ros')

    xacro_file = os.path.join(desc_share, 'urdf', 'robot.urdf.xacro')
    world_file = os.path.join(gz_share, 'worlds', 'mrf_sorting.world')

    gui = LaunchConfiguration('gui').perform(context)

    robot_description = {'robot_description': _clean_urdf(xacro_file)}

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros_share, 'launch', 'gazebo.launch.py')),
        launch_arguments={'world': world_file, 'gui': gui,
                          'verbose': 'false'}.items(),
    )

    rsp = Node(
        package='robot_state_publisher', executable='robot_state_publisher',
        output='screen',
        parameters=[robot_description, {'use_sim_time': True}],
    )

    spawn_robot = Node(
        package='gazebo_ros', executable='spawn_entity.py',
        arguments=['-topic', 'robot_description', '-entity', 'kr_arm', '-z', '0.0'],
        output='screen',
    )

    def spawner(name):
        return Node(package='controller_manager', executable='spawner',
                    arguments=[name, '--controller-manager', '/controller_manager'],
                    output='screen')

    jsb = spawner('joint_state_broadcaster')
    ctrls = [spawner(n) for n in ('arm1_controller', 'gripper1_controller')]

    # single arm clears every item -> slower belt + wider spacing so it keeps up
    conveyor = Node(package='mrf_coordinator', executable='conveyor', output='screen',
                    parameters=[{'state': 'RUNNING_SLOW'}])
    object_manager = Node(package='mrf_coordinator', executable='object_manager',
                          output='screen',
                          parameters=[{'spawn_period': 9.0}])
    perception = Node(package='mrf_perception', executable='perception', output='screen')

    # Single arm sorts all four waste types into their colour-coded bins.
    coord1 = Node(package='mrf_coordinator', executable='coordinator',
                  name='coordinator_arm1', output='screen', parameters=[{
                      'arm_name': 'arm1', 'joint_prefix': 'a1_',
                      'arm_topic': '/arm1_controller/joint_trajectory',
                      'grip_topic': '/gripper1_controller/joint_trajectory',
                      'target_categories': ['plastic', 'metal', 'glass', 'paper'],
                      'base_x': 0.0, 'base_y': 0.0, 'base_z': 0.80, 'base_yaw': 0.0,
                      'pick_x': 0.0, 'belt_y': -0.55}])

    return [
        gazebo,
        rsp,
        spawn_robot,
        # controllers come up once gazebo_ros2_control's controller_manager exists
        TimerAction(period=6.0, actions=[jsb]),
        TimerAction(period=8.0, actions=ctrls),
        # supporting nodes
        conveyor,
        object_manager,
        perception,
        TimerAction(period=13.0, actions=[coord1]),
    ]


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('gui', default_value='true'),
        OpaqueFunction(function=launch_setup),
    ])
