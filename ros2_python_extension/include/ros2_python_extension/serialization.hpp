#ifndef ROS2_PYTHON_EXTENSION_SERIALIZATION_HPP
#define ROS2_PYTHON_EXTENSION_SERIALIZATION_HPP

#include <pybind11/pybind11.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/serialization.hpp>
#include <rclcpp/duration.hpp>


namespace ros2_python_extension {
  namespace py = pybind11;

  /**
   * Convert the result of a ROS message serialized in Python to a C++ message
   * @tparam T C++ ROS message type
   * @param bytes message serialized in Python
   * @return the converted message
   */
  template<typename T>
  T fromPython(py::bytes &bytes) {
    // buffer_info is used to extract data pointer and size of bytes
    py::buffer_info info(py::buffer(bytes).request());

    // initialize serialized message struct
    rmw_serialized_message_t serialized_message = rmw_get_zero_initialized_serialized_message();
    auto allocator = rcl_get_default_allocator();
    rmw_serialized_message_init(&serialized_message, info.size, &allocator);
    serialized_message.buffer = reinterpret_cast<uint8_t *>(info.ptr);
    serialized_message.buffer_length = info.size;
    auto ts = rosidl_typesupport_cpp::get_message_type_support_handle<T>();

    T out;
    // do the deserialization
    rmw_ret_t result2 = rmw_deserialize(&serialized_message, ts, &out);
    if (result2 != RMW_RET_OK) {
      printf("Failed to deserialize message!\n");
    }

    return out;
  }

  /**
   * Convert a C++ ROS message to a Python ByteString that can be deserialized to the message
   * @tparam T C++ ROS message type
   * @param msg C++ ROS message
   * @return the message serialized into a Python ByteString
   */
  template<typename T>
  py::bytes toPython(T &msg) {
    // initialize serialized message struct
    rmw_serialized_message_t serialized_message = rmw_get_zero_initialized_serialized_message();
    auto type_support = rosidl_typesupport_cpp::get_message_type_support_handle<T>();
    auto allocator = rcl_get_default_allocator();
    rmw_serialized_message_init(&serialized_message, 0u, &allocator);

    // do the serialization
    rmw_ret_t result = rmw_serialize(&msg, type_support, &serialized_message);
    if (result != RMW_RET_OK) {
      printf("Failed to serialize message!\n");
    }

    // convert the result to python bytes by using the data and length
    return {reinterpret_cast<const char *>(serialized_message.buffer), serialized_message.buffer_length};
  }
} // namespace ros2_python_extension
#endif // ROS2_PYTHON_EXTENSION_SERIALIZATION_HPP
