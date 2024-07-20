#include <rclcpp/rclcpp.hpp>
#include "test_node.h"

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);

    rclcpp::executors::SingleThreadedExecutor exe;
    std::shared_ptr<TestNode> node = std::make_shared<TestNode>();
    exe.add_node(node->get_node_base_interface());
    exe.spin();

    rclcpp::shutdown();
    return 0;
}
