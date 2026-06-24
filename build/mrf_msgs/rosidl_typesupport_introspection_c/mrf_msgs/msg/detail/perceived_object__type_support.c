// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from mrf_msgs:msg/PerceivedObject.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "mrf_msgs/msg/detail/perceived_object__rosidl_typesupport_introspection_c.h"
#include "mrf_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "mrf_msgs/msg/detail/perceived_object__functions.h"
#include "mrf_msgs/msg/detail/perceived_object__struct.h"


// Include directives for member types
// Member `object_id`
// Member `category`
#include "rosidl_runtime_c/string_functions.h"
// Member `pose`
#include "geometry_msgs/msg/pose.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"
// Member `velocity`
#include "geometry_msgs/msg/vector3.h"
// Member `velocity`
#include "geometry_msgs/msg/detail/vector3__rosidl_typesupport_introspection_c.h"
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mrf_msgs__msg__PerceivedObject__init(message_memory);
}

void mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_fini_function(void * message_memory)
{
  mrf_msgs__msg__PerceivedObject__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_member_array[6] = {
  {
    "object_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mrf_msgs__msg__PerceivedObject, object_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "category",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mrf_msgs__msg__PerceivedObject, category),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mrf_msgs__msg__PerceivedObject, pose),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mrf_msgs__msg__PerceivedObject, velocity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "confidence",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mrf_msgs__msg__PerceivedObject, confidence),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mrf_msgs__msg__PerceivedObject, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_members = {
  "mrf_msgs__msg",  // message namespace
  "PerceivedObject",  // message name
  6,  // number of fields
  sizeof(mrf_msgs__msg__PerceivedObject),
  mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_member_array,  // message members
  mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_init_function,  // function to initialize message memory (memory has to be allocated)
  mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_type_support_handle = {
  0,
  &mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mrf_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mrf_msgs, msg, PerceivedObject)() {
  mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_type_support_handle.typesupport_identifier) {
    mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &mrf_msgs__msg__PerceivedObject__rosidl_typesupport_introspection_c__PerceivedObject_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
