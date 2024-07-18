// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from test_a_msgs:msg/Test.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "test_a_msgs/msg/detail/test__struct.h"
#include "test_a_msgs/msg/detail/test__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace test_a_msgs
{

namespace msg
{

namespace rosidl_typesupport_c
{

typedef struct _Test_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Test_type_support_ids_t;

static const _Test_type_support_ids_t _Test_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Test_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Test_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Test_type_support_symbol_names_t _Test_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, test_a_msgs, msg, Test)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, test_a_msgs, msg, Test)),
  }
};

typedef struct _Test_type_support_data_t
{
  void * data[2];
} _Test_type_support_data_t;

static _Test_type_support_data_t _Test_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Test_message_typesupport_map = {
  2,
  "test_a_msgs",
  &_Test_message_typesupport_ids.typesupport_identifier[0],
  &_Test_message_typesupport_symbol_names.symbol_name[0],
  &_Test_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Test_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Test_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace msg

}  // namespace test_a_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, test_a_msgs, msg, Test)() {
  return &::test_a_msgs::msg::rosidl_typesupport_c::Test_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
