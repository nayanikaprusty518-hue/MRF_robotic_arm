// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from mrf_msgs:msg/PerceivedObject.idl
// generated code does not contain a copyright notice
#include "mrf_msgs/msg/detail/perceived_object__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `object_id`
// Member `category`
#include "rosidl_runtime_c/string_functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"
// Member `velocity`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
mrf_msgs__msg__PerceivedObject__init(mrf_msgs__msg__PerceivedObject * msg)
{
  if (!msg) {
    return false;
  }
  // object_id
  if (!rosidl_runtime_c__String__init(&msg->object_id)) {
    mrf_msgs__msg__PerceivedObject__fini(msg);
    return false;
  }
  // category
  if (!rosidl_runtime_c__String__init(&msg->category)) {
    mrf_msgs__msg__PerceivedObject__fini(msg);
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    mrf_msgs__msg__PerceivedObject__fini(msg);
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__init(&msg->velocity)) {
    mrf_msgs__msg__PerceivedObject__fini(msg);
    return false;
  }
  // confidence
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    mrf_msgs__msg__PerceivedObject__fini(msg);
    return false;
  }
  return true;
}

void
mrf_msgs__msg__PerceivedObject__fini(mrf_msgs__msg__PerceivedObject * msg)
{
  if (!msg) {
    return;
  }
  // object_id
  rosidl_runtime_c__String__fini(&msg->object_id);
  // category
  rosidl_runtime_c__String__fini(&msg->category);
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
  // velocity
  geometry_msgs__msg__Vector3__fini(&msg->velocity);
  // confidence
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
mrf_msgs__msg__PerceivedObject__are_equal(const mrf_msgs__msg__PerceivedObject * lhs, const mrf_msgs__msg__PerceivedObject * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // object_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->object_id), &(rhs->object_id)))
  {
    return false;
  }
  // category
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->category), &(rhs->category)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
mrf_msgs__msg__PerceivedObject__copy(
  const mrf_msgs__msg__PerceivedObject * input,
  mrf_msgs__msg__PerceivedObject * output)
{
  if (!input || !output) {
    return false;
  }
  // object_id
  if (!rosidl_runtime_c__String__copy(
      &(input->object_id), &(output->object_id)))
  {
    return false;
  }
  // category
  if (!rosidl_runtime_c__String__copy(
      &(input->category), &(output->category)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // velocity
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // confidence
  output->confidence = input->confidence;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

mrf_msgs__msg__PerceivedObject *
mrf_msgs__msg__PerceivedObject__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mrf_msgs__msg__PerceivedObject * msg = (mrf_msgs__msg__PerceivedObject *)allocator.allocate(sizeof(mrf_msgs__msg__PerceivedObject), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mrf_msgs__msg__PerceivedObject));
  bool success = mrf_msgs__msg__PerceivedObject__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
mrf_msgs__msg__PerceivedObject__destroy(mrf_msgs__msg__PerceivedObject * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    mrf_msgs__msg__PerceivedObject__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
mrf_msgs__msg__PerceivedObject__Sequence__init(mrf_msgs__msg__PerceivedObject__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mrf_msgs__msg__PerceivedObject * data = NULL;

  if (size) {
    data = (mrf_msgs__msg__PerceivedObject *)allocator.zero_allocate(size, sizeof(mrf_msgs__msg__PerceivedObject), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mrf_msgs__msg__PerceivedObject__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mrf_msgs__msg__PerceivedObject__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
mrf_msgs__msg__PerceivedObject__Sequence__fini(mrf_msgs__msg__PerceivedObject__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      mrf_msgs__msg__PerceivedObject__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

mrf_msgs__msg__PerceivedObject__Sequence *
mrf_msgs__msg__PerceivedObject__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mrf_msgs__msg__PerceivedObject__Sequence * array = (mrf_msgs__msg__PerceivedObject__Sequence *)allocator.allocate(sizeof(mrf_msgs__msg__PerceivedObject__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = mrf_msgs__msg__PerceivedObject__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
mrf_msgs__msg__PerceivedObject__Sequence__destroy(mrf_msgs__msg__PerceivedObject__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    mrf_msgs__msg__PerceivedObject__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
mrf_msgs__msg__PerceivedObject__Sequence__are_equal(const mrf_msgs__msg__PerceivedObject__Sequence * lhs, const mrf_msgs__msg__PerceivedObject__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!mrf_msgs__msg__PerceivedObject__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
mrf_msgs__msg__PerceivedObject__Sequence__copy(
  const mrf_msgs__msg__PerceivedObject__Sequence * input,
  mrf_msgs__msg__PerceivedObject__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(mrf_msgs__msg__PerceivedObject);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    mrf_msgs__msg__PerceivedObject * data =
      (mrf_msgs__msg__PerceivedObject *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!mrf_msgs__msg__PerceivedObject__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          mrf_msgs__msg__PerceivedObject__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!mrf_msgs__msg__PerceivedObject__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
