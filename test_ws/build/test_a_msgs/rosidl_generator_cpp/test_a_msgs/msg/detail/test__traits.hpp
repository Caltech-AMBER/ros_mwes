// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from test_a_msgs:msg/Test.idl
// generated code does not contain a copyright notice

#ifndef TEST_A_MSGS__MSG__DETAIL__TEST__TRAITS_HPP_
#define TEST_A_MSGS__MSG__DETAIL__TEST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "test_a_msgs/msg/detail/test__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace test_a_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Test & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Test & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Test & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace test_a_msgs

namespace rosidl_generator_traits
{

[[deprecated("use test_a_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const test_a_msgs::msg::Test & msg,
  std::ostream & out, size_t indentation = 0)
{
  test_a_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use test_a_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const test_a_msgs::msg::Test & msg)
{
  return test_a_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<test_a_msgs::msg::Test>()
{
  return "test_a_msgs::msg::Test";
}

template<>
inline const char * name<test_a_msgs::msg::Test>()
{
  return "test_a_msgs/msg/Test";
}

template<>
struct has_fixed_size<test_a_msgs::msg::Test>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<test_a_msgs::msg::Test>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<test_a_msgs::msg::Test>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TEST_A_MSGS__MSG__DETAIL__TEST__TRAITS_HPP_
