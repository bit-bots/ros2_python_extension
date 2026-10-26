cmake_minimum_required(VERSION 3.10)
project(ros2_python_extension)

# Add support for C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

set(PYBIND11_PYTHON_VERSION 3)
set(PYBIND11_FINDPYTHON ON)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(pybind11 REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_library(ros2_python_extension INTERFACE)
target_include_directories(ros2_python_extension INTERFACE include)

target_link_libraries(ros2_python_extension INTERFACE
  rclcpp::rclcpp
  pybind11::headers
  Python3::Python
)

install(DIRECTORY include/ DESTINATION include)

ament_export_dependencies(rclcpp)
ament_export_dependencies(pybind11)
ament_export_dependencies(Python3)
ament_export_include_directories(include)

ament_package()
