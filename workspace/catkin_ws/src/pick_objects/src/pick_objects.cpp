#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

const float pickup_x = 5.06;
const float pickup_y = -1.49;
const float pickup_o = -1.26;
const float dropoff_x = -8.38;
const float dropoff_y = 2.83;
const float dropoff_o = 1.94;


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
  goal.target_pose.pose.position.x = pickup_x;
  goal.target_pose.pose.position.y = pickup_y;
  goal.target_pose.pose.orientation.w = pickup_o;

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
  goal.target_pose.pose.position.x = dropoff_x;
  goal.target_pose.pose.position.y = dropoff_y;
  goal.target_pose.pose.orientation.w = dropoff_o;

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
