// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from test_a_msgs:msg/Test.idl
// generated code does not contain a copyright notice

#ifndef TEST_A_MSGS__MSG__DETAIL__TEST__STRUCT_H_
#define TEST_A_MSGS__MSG__DETAIL__TEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/Test in the package test_a_msgs.
typedef struct test_a_msgs__msg__Test
{
  std_msgs__msg__Header header;
} test_a_msgs__msg__Test;

// Struct for a sequence of test_a_msgs__msg__Test.
typedef struct test_a_msgs__msg__Test__Sequence
{
  test_a_msgs__msg__Test * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} test_a_msgs__msg__Test__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TEST_A_MSGS__MSG__DETAIL__TEST__STRUCT_H_
