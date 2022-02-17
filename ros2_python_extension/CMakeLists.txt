cmake_minimum_required(VERSION 3.5)
project(ros2_python_extension)

# Add support for C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(pybind11 REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

add_library(ros2_python_extension INTERFACE)
target_include_directories(ros2_python_extension INTERFACE include)

ament_target_dependencies(ros2_python_extension INTERFACE
  pybind11
  Python3
)

install(DIRECTORY include/ DESTINATION include)

ament_export_dependencies(pybind11)
ament_export_dependencies(Python3)
ament_export_include_directories(include)

ament_package()