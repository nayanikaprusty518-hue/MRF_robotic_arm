// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from mrf_msgs:msg/PerceivedObject.idl
// generated code does not contain a copyright notice

#ifndef MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__FUNCTIONS_H_
#define MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "mrf_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "mrf_msgs/msg/detail/perceived_object__struct.h"

/// Initialize msg/PerceivedObject message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * mrf_msgs__msg__PerceivedObject
 * )) before or use
 * mrf_msgs__msg__PerceivedObject__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
bool
mrf_msgs__msg__PerceivedObject__init(mrf_msgs__msg__PerceivedObject * msg);

/// Finalize msg/PerceivedObject message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
void
mrf_msgs__msg__PerceivedObject__fini(mrf_msgs__msg__PerceivedObject * msg);

/// Create msg/PerceivedObject message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * mrf_msgs__msg__PerceivedObject__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
mrf_msgs__msg__PerceivedObject *
mrf_msgs__msg__PerceivedObject__create();

/// Destroy msg/PerceivedObject message.
/**
 * It calls
 * mrf_msgs__msg__PerceivedObject__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
void
mrf_msgs__msg__PerceivedObject__destroy(mrf_msgs__msg__PerceivedObject * msg);

/// Check for msg/PerceivedObject message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
bool
mrf_msgs__msg__PerceivedObject__are_equal(const mrf_msgs__msg__PerceivedObject * lhs, const mrf_msgs__msg__PerceivedObject * rhs);

/// Copy a msg/PerceivedObject message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
bool
mrf_msgs__msg__PerceivedObject__copy(
  const mrf_msgs__msg__PerceivedObject * input,
  mrf_msgs__msg__PerceivedObject * output);

/// Initialize array of msg/PerceivedObject messages.
/**
 * It allocates the memory for the number of elements and calls
 * mrf_msgs__msg__PerceivedObject__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
bool
mrf_msgs__msg__PerceivedObject__Sequence__init(mrf_msgs__msg__PerceivedObject__Sequence * array, size_t size);

/// Finalize array of msg/PerceivedObject messages.
/**
 * It calls
 * mrf_msgs__msg__PerceivedObject__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
void
mrf_msgs__msg__PerceivedObject__Sequence__fini(mrf_msgs__msg__PerceivedObject__Sequence * array);

/// Create array of msg/PerceivedObject messages.
/**
 * It allocates the memory for the array and calls
 * mrf_msgs__msg__PerceivedObject__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
mrf_msgs__msg__PerceivedObject__Sequence *
mrf_msgs__msg__PerceivedObject__Sequence__create(size_t size);

/// Destroy array of msg/PerceivedObject messages.
/**
 * It calls
 * mrf_msgs__msg__PerceivedObject__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
void
mrf_msgs__msg__PerceivedObject__Sequence__destroy(mrf_msgs__msg__PerceivedObject__Sequence * array);

/// Check for msg/PerceivedObject message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
bool
mrf_msgs__msg__PerceivedObject__Sequence__are_equal(const mrf_msgs__msg__PerceivedObject__Sequence * lhs, const mrf_msgs__msg__PerceivedObject__Sequence * rhs);

/// Copy an array of msg/PerceivedObject messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_mrf_msgs
bool
mrf_msgs__msg__PerceivedObject__Sequence__copy(
  const mrf_msgs__msg__PerceivedObject__Sequence * input,
  mrf_msgs__msg__PerceivedObject__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__FUNCTIONS_H_
