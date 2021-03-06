/*******************************************************************************
 *  Copyright (c) Gezp (https://github.com/gezp), All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it 
 *  under the terms of the MIT License, See the MIT License for more details.
 *
 *  You should have received a copy of the MIT License along with this program.
 *  If not, see <https://opensource.org/licenses/MIT/>.
 *
 ******************************************************************************/
#ifndef UNIVERSAL_ROBOT_IGN_JOINT_TRAJECTORY_CONTROLLER_H
#define UNIVERSAL_ROBOT_IGN_JOINT_TRAJECTORY_CONTROLLER_H

#include <ignition/transport/Node.hh>
#include <mutex>
#include <rclcpp/rclcpp.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <unordered_map>

namespace universal_robot_ign {

class jointTrajectoryController {
public:
    jointTrajectoryController(const rclcpp::Node::SharedPtr& nh,
        const std::vector<std::string>& joint_names,
        const std::string& ros_cmd_topic,
        const std::vector<std::string>& ign_cmd_topics,
        const unsigned int update_rate);
    ~jointTrajectoryController() {};

private:
    void setJointTrajectoryCb(const trajectory_msgs::msg::JointTrajectory::SharedPtr);
    void updatePositionTimerCb();

private:
    rclcpp::Node::SharedPtr nh_;
    std::shared_ptr<ignition::transport::Node> ign_node_;
    // ros pub and sub
    rclcpp::Subscription<trajectory_msgs::msg::JointTrajectory>::SharedPtr ros_cmd_joint_trajectory_sub_;
    //ignition pub
    std::vector<std::shared_ptr<ignition::transport::Node::Publisher>> ign_cmd_joint_pubs_;
    rclcpp::TimerBase::SharedPtr update_position_timer_;
    // joint names and map
    std::vector<std::string> joint_names_;
    size_t joint_num_;
    std::vector<double> target_positions_;
    std::unordered_map<std::string, int> joint_names_map_;
    std::mutex trajectory_mut_;
    std::vector<trajectory_msgs::msg::JointTrajectoryPoint> points_;
    rclcpp::Time trajectory_start_time_;
    unsigned int trajectory_index_;
    bool has_trajectory_ { false };

};
}
#endif //UNIVERSAL_ROBOT_IGN_JOINT_TRAJECTORY_CONTROLLER_H