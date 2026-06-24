// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mrf_msgs:msg/PerceivedObject.idl
// generated code does not contain a copyright notice

#ifndef MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__STRUCT_H_
#define MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'object_id'
// Member 'category'
#include "rosidl_runtime_c/string.h"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/PerceivedObject in the package mrf_msgs.
/**
  * A single object reported by the (simulated or real) perception layer.
  * Mirrors the perception interface defined in guide.md sections 30-32.
 */
typedef struct mrf_msgs__msg__PerceivedObject
{
  /// unique id, e.g. "obj_001"
  rosidl_runtime_c__String object_id;
  /// "plastic", "aluminum", "cardboard", ...
  rosidl_runtime_c__String category;
  /// full position + orientation in world frame
  geometry_msgs__msg__Pose pose;
  /// linear velocity (m/s), world frame
  geometry_msgs__msg__Vector3 velocity;
  /// 0.0 .. 1.0
  double confidence;
  /// time the observation was made
  builtin_interfaces__msg__Time stamp;
} mrf_msgs__msg__PerceivedObject;

// Struct for a sequence of mrf_msgs__msg__PerceivedObject.
typedef struct mrf_msgs__msg__PerceivedObject__Sequence
{
  mrf_msgs__msg__PerceivedObject * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mrf_msgs__msg__PerceivedObject__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__STRUCT_H_
