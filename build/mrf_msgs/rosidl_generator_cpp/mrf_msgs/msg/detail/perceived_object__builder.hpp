// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mrf_msgs:msg/PerceivedObject.idl
// generated code does not contain a copyright notice

#ifndef MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__BUILDER_HPP_
#define MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mrf_msgs/msg/detail/perceived_object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mrf_msgs
{

namespace msg
{

namespace builder
{

class Init_PerceivedObject_stamp
{
public:
  explicit Init_PerceivedObject_stamp(::mrf_msgs::msg::PerceivedObject & msg)
  : msg_(msg)
  {}
  ::mrf_msgs::msg::PerceivedObject stamp(::mrf_msgs::msg::PerceivedObject::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mrf_msgs::msg::PerceivedObject msg_;
};

class Init_PerceivedObject_confidence
{
public:
  explicit Init_PerceivedObject_confidence(::mrf_msgs::msg::PerceivedObject & msg)
  : msg_(msg)
  {}
  Init_PerceivedObject_stamp confidence(::mrf_msgs::msg::PerceivedObject::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_PerceivedObject_stamp(msg_);
  }

private:
  ::mrf_msgs::msg::PerceivedObject msg_;
};

class Init_PerceivedObject_velocity
{
public:
  explicit Init_PerceivedObject_velocity(::mrf_msgs::msg::PerceivedObject & msg)
  : msg_(msg)
  {}
  Init_PerceivedObject_confidence velocity(::mrf_msgs::msg::PerceivedObject::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_PerceivedObject_confidence(msg_);
  }

private:
  ::mrf_msgs::msg::PerceivedObject msg_;
};

class Init_PerceivedObject_pose
{
public:
  explicit Init_PerceivedObject_pose(::mrf_msgs::msg::PerceivedObject & msg)
  : msg_(msg)
  {}
  Init_PerceivedObject_velocity pose(::mrf_msgs::msg::PerceivedObject::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_PerceivedObject_velocity(msg_);
  }

private:
  ::mrf_msgs::msg::PerceivedObject msg_;
};

class Init_PerceivedObject_category
{
public:
  explicit Init_PerceivedObject_category(::mrf_msgs::msg::PerceivedObject & msg)
  : msg_(msg)
  {}
  Init_PerceivedObject_pose category(::mrf_msgs::msg::PerceivedObject::_category_type arg)
  {
    msg_.category = std::move(arg);
    return Init_PerceivedObject_pose(msg_);
  }

private:
  ::mrf_msgs::msg::PerceivedObject msg_;
};

class Init_PerceivedObject_object_id
{
public:
  Init_PerceivedObject_object_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PerceivedObject_category object_id(::mrf_msgs::msg::PerceivedObject::_object_id_type arg)
  {
    msg_.object_id = std::move(arg);
    return Init_PerceivedObject_category(msg_);
  }

private:
  ::mrf_msgs::msg::PerceivedObject msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mrf_msgs::msg::PerceivedObject>()
{
  return mrf_msgs::msg::builder::Init_PerceivedObject_object_id();
}

}  // namespace mrf_msgs

#endif  // MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__BUILDER_HPP_
