cmake_minimum_required(VERSION 3.8)
project(test_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(test_a_msgs REQUIRED)
find_package(test_b_msgs REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
  ament_cmake
  rclcpp
  test_a_msgs
  test_b_msgs
)
include_directories(${THIS_PACKAGE_INCLUDE_DEPENDS})

add_executable(test_node src/test_node.cpp)
target_include_directories(
  test_node
  PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)
ament_target_dependencies(test_node
  ${THIS_PACKAGE_INCLUDE_DEPENDS})

install(TARGETS
  test_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
