#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to mrf_msgs__msg__PerceivedObject
/// A single object reported by the (simulated or real) perception layer.
/// Mirrors the perception interface defined in guide.md sections 30-32.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PerceivedObject {
    /// unique id, e.g. "obj_001"
    pub object_id: std::string::String,

    /// "plastic", "aluminum", "cardboard", ...
    pub category: std::string::String,

    /// full position + orientation in world frame
    pub pose: geometry_msgs::msg::Pose,

    /// linear velocity (m/s), world frame
    pub velocity: geometry_msgs::msg::Vector3,

    /// 0.0 .. 1.0
    pub confidence: f64,

    /// time the observation was made
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for PerceivedObject {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PerceivedObject::default())
  }
}

impl rosidl_runtime_rs::Message for PerceivedObject {
  type RmwMsg = super::msg::rmw::PerceivedObject;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        object_id: msg.object_id.as_str().into(),
        category: msg.category.as_str().into(),
        pose: geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Owned(msg.pose)).into_owned(),
        velocity: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(msg.velocity)).into_owned(),
        confidence: msg.confidence,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        object_id: msg.object_id.as_str().into(),
        category: msg.category.as_str().into(),
        pose: geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Borrowed(&msg.pose)).into_owned(),
        velocity: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(&msg.velocity)).into_owned(),
      confidence: msg.confidence,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      object_id: msg.object_id.to_string(),
      category: msg.category.to_string(),
      pose: geometry_msgs::msg::Pose::from_rmw_message(msg.pose),
      velocity: geometry_msgs::msg::Vector3::from_rmw_message(msg.velocity),
      confidence: msg.confidence,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to mrf_msgs__msg__PerceivedObjectArray
/// A snapshot of every object currently visible to the perception layer.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PerceivedObjectArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub objects: Vec<super::msg::PerceivedObject>,

}



impl Default for PerceivedObjectArray {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PerceivedObjectArray::default())
  }
}

impl rosidl_runtime_rs::Message for PerceivedObjectArray {
  type RmwMsg = super::msg::rmw::PerceivedObjectArray;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        objects: msg.objects
          .into_iter()
          .map(|elem| super::msg::PerceivedObject::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        objects: msg.objects
          .iter()
          .map(|elem| super::msg::PerceivedObject::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      objects: msg.objects
          .into_iter()
          .map(super::msg::PerceivedObject::from_rmw_message)
          .collect(),
    }
  }
}


