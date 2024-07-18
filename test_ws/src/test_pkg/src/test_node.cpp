#include <rclcpp/rclcpp.hpp>
#include "test_a_msgs/msg/test_a.hpp"
#include "test_b_msgs/msg/test_b.hpp"

class TestNode : public rclcpp::Node {
public:
    TestNode() : Node("test_node") {
        pub_ = this->create_publisher<test_b_msgs::msg::TestB>("test_topic", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), [this]() {
            test_a_msgs::msg::TestA msg_a;
            msg_a.header.stamp = this->now();
            pub_->publish(msg_a);

            test_b_msgs::msg::TestB msg_b;
            msg_b.header.stamp = this->now();
            msg_b.test = msg_a;

            pub_->publish(msg_b);
            RCLCPP_INFO(this->get_logger(), "Publishing message");
        });
    }
private:
    rclcpp::Publisher<test_b_msgs::msg::TestB>::SharedPtr pub_;
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
