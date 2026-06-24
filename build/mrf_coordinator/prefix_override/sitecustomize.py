import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/nayanika/robotic_arm_ws/install/mrf_coordinator'
