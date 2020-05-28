#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a pickup position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -1.44;
  goal.target_pose.pose.position.y = -5.18;
  goal.target_pose.pose.orientation.w = -0.14;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Pickup location reached!");
  else
    ROS_INFO("Failed to move to pickup location");

  ros::Duration(5.0).sleep();

  // Define a drop off position and orientation for the robot to reach
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = 2.508;
  goal.target_pose.pose.position.y = 8.382;
  goal.target_pose.pose.orientation.w = 0.99;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Drop off location reached!");
  else
    ROS_INFO("Failed to move to drop off location");

  return 0;
}
