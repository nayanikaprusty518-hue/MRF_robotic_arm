# A single object reported by the (simulated or real) perception layer.
# Mirrors the perception interface defined in guide.md sections 30-32.

string   object_id        # unique id, e.g. "obj_001"
string   category         # "plastic", "aluminum", "cardboard", ...
geometry_msgs/Pose pose   # full position + orientation in world frame
geometry_msgs/Vector3 velocity   # linear velocity (m/s), world frame
float64  confidence       # 0.0 .. 1.0
builtin_interfaces/Time stamp    # time the observation was made
