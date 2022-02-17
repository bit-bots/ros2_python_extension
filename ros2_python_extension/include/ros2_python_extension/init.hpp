#ifndef ROS2_PYTHON_EXTENSION_INIT_HPP
#define ROS2_PYTHON_EXTENSION_INIT_HPP

namespace ros2_python_extension {
  void initRos() {
    rclcpp::init(0, nullptr);
  }
}

#endif // ROS2_PYTHON_EXTENSION_INIT_HPP
