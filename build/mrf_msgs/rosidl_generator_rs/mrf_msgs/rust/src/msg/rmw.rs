#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "mrf_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__mrf_msgs__msg__PerceivedObject() -> *const std::ffi::c_void;
}

#[link(name = "mrf_msgs__rosidl_generator_c")]
extern "C" {
    fn mrf_msgs__msg__PerceivedObject__init(msg: *mut PerceivedObject) -> bool;
    fn mrf_msgs__msg__PerceivedObject__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PerceivedObject>, size: usize) -> bool;
    fn mrf_msgs__msg__PerceivedObject__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PerceivedObject>);
    fn mrf_msgs__msg__PerceivedObject__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PerceivedObject>, out_seq: *mut rosidl_runtime_rs::Sequence<PerceivedObject>) -> bool;
}

// Corresponds to mrf_msgs__msg__PerceivedObject
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// A single object reported by the (simulated or real) perception layer.
/// Mirrors the perception interface defined in guide.md sections 30-32.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PerceivedObject {
    /// unique id, e.g. "obj_001"
    pub object_id: rosidl_runtime_rs::String,

    /// "plastic", "aluminum", "cardboard", ...
    pub category: rosidl_runtime_rs::String,

    /// full position + orientation in world frame
    pub pose: geometry_msgs::msg::rmw::Pose,

    /// linear velocity (m/s), world frame
    pub velocity: geometry_msgs::msg::rmw::Vector3,

    /// 0.0 .. 1.0
    pub confidence: f64,

    /// time the observation was made
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for PerceivedObject {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !mrf_msgs__msg__PerceivedObject__init(&mut msg as *mut _) {
        panic!("Call to mrf_msgs__msg__PerceivedObject__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PerceivedObject {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { mrf_msgs__msg__PerceivedObject__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { mrf_msgs__msg__PerceivedObject__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { mrf_msgs__msg__PerceivedObject__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PerceivedObject {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PerceivedObject where Self: Sized {
  const TYPE_NAME: &'static str = "mrf_msgs/msg/PerceivedObject";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__mrf_msgs__msg__PerceivedObject() }
  }
}


#[link(name = "mrf_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__mrf_msgs__msg__PerceivedObjectArray() -> *const std::ffi::c_void;
}

#[link(name = "mrf_msgs__rosidl_generator_c")]
extern "C" {
    fn mrf_msgs__msg__PerceivedObjectArray__init(msg: *mut PerceivedObjectArray) -> bool;
    fn mrf_msgs__msg__PerceivedObjectArray__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PerceivedObjectArray>, size: usize) -> bool;
    fn mrf_msgs__msg__PerceivedObjectArray__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PerceivedObjectArray>);
    fn mrf_msgs__msg__PerceivedObjectArray__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PerceivedObjectArray>, out_seq: *mut rosidl_runtime_rs::Sequence<PerceivedObjectArray>) -> bool;
}

// Corresponds to mrf_msgs__msg__PerceivedObjectArray
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// A snapshot of every object currently visible to the perception layer.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PerceivedObjectArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub objects: rosidl_runtime_rs::Sequence<super::super::msg::rmw::PerceivedObject>,

}



impl Default for PerceivedObjectArray {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !mrf_msgs__msg__PerceivedObjectArray__init(&mut msg as *mut _) {
        panic!("Call to mrf_msgs__msg__PerceivedObjectArray__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PerceivedObjectArray {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { mrf_msgs__msg__PerceivedObjectArray__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { mrf_msgs__msg__PerceivedObjectArray__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { mrf_msgs__msg__PerceivedObjectArray__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PerceivedObjectArray {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PerceivedObjectArray where Self: Sized {
  const TYPE_NAME: &'static str = "mrf_msgs/msg/PerceivedObjectArray";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__mrf_msgs__msg__PerceivedObjectArray() }
  }
}


