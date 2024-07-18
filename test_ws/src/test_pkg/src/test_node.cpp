#include <rclcpp/rclcpp.hpp>
#include "test_a_msgs/msg/test.hpp"

class TestNode : public rclcpp::Node {
public:
    TestNode() : Node("test_node") {
        pub_ = this->create_publisher<test_a_msgs::msg::Test>("test_topic", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), [this]() {
            test_a_msgs::msg::Test msg;
            msg.header.stamp = this->now();
            pub_->publish(msg);
            RCLCPP_INFO(this->get_logger(), "Publishing message");
        });
    }
private:
    rclcpp::Publisher<test_a_msgs::msg::Test>::SharedPtr pub_;
    // make a timer
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);

    rclcpp::executors::SingleThreadedExecutor exe;
    std::shared_ptr<TestNode> node = std::make_shared<TestNode>();
    exe.add_node(node->get_node_base_interface());
    exe.spin();

    rclcpp::shutdown();
    return 0;
}
