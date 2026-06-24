// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from mrf_msgs:msg/PerceivedObject.idl
// generated code does not contain a copyright notice

#ifndef MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__STRUCT_HPP_
#define MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"
// Member 'velocity'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__mrf_msgs__msg__PerceivedObject __attribute__((deprecated))
#else
# define DEPRECATED__mrf_msgs__msg__PerceivedObject __declspec(deprecated)
#endif

namespace mrf_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PerceivedObject_
{
  using Type = PerceivedObject_<ContainerAllocator>;

  explicit PerceivedObject_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init),
    velocity(_init),
    stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->object_id = "";
      this->category = "";
      this->confidence = 0.0;
    }
  }

  explicit PerceivedObject_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : object_id(_alloc),
    category(_alloc),
    pose(_alloc, _init),
    velocity(_alloc, _init),
    stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->object_id = "";
      this->category = "";
      this->confidence = 0.0;
    }
  }

  // field types and members
  using _object_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _object_id_type object_id;
  using _category_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _category_type category;
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;
  using _velocity_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _velocity_type velocity;
  using _confidence_type =
    double;
  _confidence_type confidence;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__object_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->object_id = _arg;
    return *this;
  }
  Type & set__category(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->category = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__velocity(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__confidence(
    const double & _arg)
  {
    this->confidence = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mrf_msgs::msg::PerceivedObject_<ContainerAllocator> *;
  using ConstRawPtr =
    const mrf_msgs::msg::PerceivedObject_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mrf_msgs::msg::PerceivedObject_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mrf_msgs::msg::PerceivedObject_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mrf_msgs::msg::PerceivedObject_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mrf_msgs::msg::PerceivedObject_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mrf_msgs::msg::PerceivedObject_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mrf_msgs::msg::PerceivedObject_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mrf_msgs::msg::PerceivedObject_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mrf_msgs::msg::PerceivedObject_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mrf_msgs__msg__PerceivedObject
    std::shared_ptr<mrf_msgs::msg::PerceivedObject_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mrf_msgs__msg__PerceivedObject
    std::shared_ptr<mrf_msgs::msg::PerceivedObject_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PerceivedObject_ & other) const
  {
    if (this->object_id != other.object_id) {
      return false;
    }
    if (this->category != other.category) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const PerceivedObject_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PerceivedObject_

// alias to use template instance with default allocator
using PerceivedObject =
  mrf_msgs::msg::PerceivedObject_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace mrf_msgs

#endif  // MRF_MSGS__MSG__DETAIL__PERCEIVED_OBJECT__STRUCT_HPP_
