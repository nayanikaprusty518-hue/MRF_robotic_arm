// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mrf_msgs:msg/PerceivedObjectArray.idl
// generated code does not contain a copyright notice

#ifndef MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT_ARRAY__STRUCT_H_
#define MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'objects'
#include "mrf_msgs/msg/detail/perceived_object__struct.h"

/// Struct defined in msg/PerceivedObjectArray in the package mrf_msgs.
/**
  * A snapshot of every object currently visible to the perception layer.
 */
typedef struct mrf_msgs__msg__PerceivedObjectArray
{
  std_msgs__msg__Header header;
  mrf_msgs__msg__PerceivedObject__Sequence objects;
} mrf_msgs__msg__PerceivedObjectArray;

// Struct for a sequence of mrf_msgs__msg__PerceivedObjectArray.
typedef struct mrf_msgs__msg__PerceivedObjectArray__Sequence
{
  mrf_msgs__msg__PerceivedObjectArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mrf_msgs__msg__PerceivedObjectArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT_ARRAY__STRUCT_H_
