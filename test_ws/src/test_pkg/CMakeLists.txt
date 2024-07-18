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

# make a header only lib
add_library(test_lib INTERFACE)
target_include_directories(test_lib INTERFACE include)

ament_target_dependencies(test_lib INTERFACE
  ament_cmake
  rclcpp
  test_a_msgs
  test_b_msgs)


# make the executable
add_executable(test_node src/test_node.cpp)
target_link_libraries(test_node PUBLIC test_lib)

install(TARGETS
  test_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
