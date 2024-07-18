#include <rclcpp/rclcpp.hpp>
#include "test_a_msgs/msg/test_a.hpp"
#include "test_b_msgs/msg/test_b.hpp"

class TestNode : public rclcpp::Node {
public:
    TestNode() : Node("test_node") {
        pub_a_ = this->create_publisher<test_a_msgs::msg::TestA>("test_topic_a", 10);
        pub_b_ = this->create_publisher<test_b_msgs::msg::TestB>("test_topic_b", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), [this]() {
            test_a_msgs::msg::TestA msg_a;
            msg_a.header.stamp = this->now();
            pub_a_->publish(msg_a);

            test_b_msgs::msg::TestB msg_b;
            msg_b.header.stamp = this->now();
            msg_b.test = msg_a;

            pub_b_->publish(msg_b);
            RCLCPP_INFO(this->get_logger(), "Publishing message");
        });
    }
private:
    rclcpp::Publisher<test_a_msgs::msg::TestA>::SharedPtr pub_a_;
    rclcpp::Publisher<test_b_msgs::msg::TestB>::SharedPtr pub_b_;
    rclcpp::TimerBase::SharedPtr timer_;
};
