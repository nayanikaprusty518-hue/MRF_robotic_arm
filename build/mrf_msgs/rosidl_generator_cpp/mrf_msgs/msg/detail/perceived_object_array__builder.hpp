// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mrf_msgs:msg/PerceivedObjectArray.idl
// generated code does not contain a copyright notice

#ifndef MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT_ARRAY__BUILDER_HPP_
#define MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mrf_msgs/msg/detail/perceived_object_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mrf_msgs
{

namespace msg
{

namespace builder
{

class Init_PerceivedObjectArray_objects
{
public:
  explicit Init_PerceivedObjectArray_objects(::mrf_msgs::msg::PerceivedObjectArray & msg)
  : msg_(msg)
  {}
  ::mrf_msgs::msg::PerceivedObjectArray objects(::mrf_msgs::msg::PerceivedObjectArray::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mrf_msgs::msg::PerceivedObjectArray msg_;
};

class Init_PerceivedObjectArray_header
{
public:
  Init_PerceivedObjectArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PerceivedObjectArray_objects header(::mrf_msgs::msg::PerceivedObjectArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PerceivedObjectArray_objects(msg_);
  }

private:
  ::mrf_msgs::msg::PerceivedObjectArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mrf_msgs::msg::PerceivedObjectArray>()
{
  return mrf_msgs::msg::builder::Init_PerceivedObjectArray_header();
}

}  // namespace mrf_msgs

#endif  // MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT_ARRAY__BUILDER_HPP_
