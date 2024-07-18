// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from test_a_msgs:msg/Test.idl
// generated code does not contain a copyright notice

#ifndef TEST_A_MSGS__MSG__DETAIL__TEST__BUILDER_HPP_
#define TEST_A_MSGS__MSG__DETAIL__TEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "test_a_msgs/msg/detail/test__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace test_a_msgs
{

namespace msg
{

namespace builder
{

class Init_Test_header
{
public:
  Init_Test_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::test_a_msgs::msg::Test header(::test_a_msgs::msg::Test::_header_type arg)
  {
    msg_.header = std::move(arg);
    return std::move(msg_);
  }

private:
  ::test_a_msgs::msg::Test msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::test_a_msgs::msg::Test>()
{
  return test_a_msgs::msg::builder::Init_Test_header();
}

}  // namespace test_a_msgs

#endif  // TEST_A_MSGS__MSG__DETAIL__TEST__BUILDER_HPP_
