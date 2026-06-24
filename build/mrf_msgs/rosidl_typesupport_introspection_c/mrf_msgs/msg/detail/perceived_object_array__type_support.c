// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from mrf_msgs:msg/PerceivedObjectArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "mrf_msgs/msg/detail/perceived_object_array__rosidl_typesupport_introspection_c.h"
#include "mrf_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "mrf_msgs/msg/detail/perceived_object_array__functions.h"
#include "mrf_msgs/msg/detail/perceived_object_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `objects`
#include "mrf_msgs/msg/perceived_object.h"
// Member `objects`
#include "mrf_msgs/msg/detail/perceived_object__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mrf_msgs__msg__PerceivedObjectArray__init(message_memory);
}

void mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_fini_function(void * message_memory)
{
  mrf_msgs__msg__PerceivedObjectArray__fini(message_memory);
}

size_t mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__size_function__PerceivedObjectArray__objects(
  const void * untyped_member)
{
  const mrf_msgs__msg__PerceivedObject__Sequence * member =
    (const mrf_msgs__msg__PerceivedObject__Sequence *)(untyped_member);
  return member->size;
}

const void * mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__get_const_function__PerceivedObjectArray__objects(
  const void * untyped_member, size_t index)
{
  const mrf_msgs__msg__PerceivedObject__Sequence * member =
    (const mrf_msgs__msg__PerceivedObject__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__get_function__PerceivedObjectArray__objects(
  void * untyped_member, size_t index)
{
  mrf_msgs__msg__PerceivedObject__Sequence * member =
    (mrf_msgs__msg__PerceivedObject__Sequence *)(untyped_member);
  return &member->data[index];
}

void mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__fetch_function__PerceivedObjectArray__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const mrf_msgs__msg__PerceivedObject * item =
    ((const mrf_msgs__msg__PerceivedObject *)
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__get_const_function__PerceivedObjectArray__objects(untyped_member, index));
  mrf_msgs__msg__PerceivedObject * value =
    (mrf_msgs__msg__PerceivedObject *)(untyped_value);
  *value = *item;
}

void mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__assign_function__PerceivedObjectArray__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  mrf_msgs__msg__PerceivedObject * item =
    ((mrf_msgs__msg__PerceivedObject *)
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__get_function__PerceivedObjectArray__objects(untyped_member, index));
  const mrf_msgs__msg__PerceivedObject * value =
    (const mrf_msgs__msg__PerceivedObject *)(untyped_value);
  *item = *value;
}

bool mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__resize_function__PerceivedObjectArray__objects(
  void * untyped_member, size_t size)
{
  mrf_msgs__msg__PerceivedObject__Sequence * member =
    (mrf_msgs__msg__PerceivedObject__Sequence *)(untyped_member);
  mrf_msgs__msg__PerceivedObject__Sequence__fini(member);
  return mrf_msgs__msg__PerceivedObject__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mrf_msgs__msg__PerceivedObjectArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mrf_msgs__msg__PerceivedObjectArray, objects),  // bytes offset in struct
    NULL,  // default value
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__size_function__PerceivedObjectArray__objects,  // size() function pointer
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__get_const_function__PerceivedObjectArray__objects,  // get_const(index) function pointer
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__get_function__PerceivedObjectArray__objects,  // get(index) function pointer
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__fetch_function__PerceivedObjectArray__objects,  // fetch(index, &value) function pointer
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__assign_function__PerceivedObjectArray__objects,  // assign(index, value) function pointer
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__resize_function__PerceivedObjectArray__objects  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_members = {
  "mrf_msgs__msg",  // message namespace
  "PerceivedObjectArray",  // message name
  2,  // number of fields
  sizeof(mrf_msgs__msg__PerceivedObjectArray),
  mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_member_array,  // message members
  mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_init_function,  // function to initialize message memory (memory has to be allocated)
  mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_type_support_handle = {
  0,
  &mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mrf_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mrf_msgs, msg, PerceivedObjectArray)() {
  mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mrf_msgs, msg, PerceivedObject)();
  if (!mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_type_support_handle.typesupport_identifier) {
    mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &mrf_msgs__msg__PerceivedObjectArray__rosidl_typesupport_introspection_c__PerceivedObjectArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
