#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/ernesto/udacity/robotics/Project3/workspace/catkin_ws/src/map/myworld.world" & 
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/ernesto/udacity/robotics/Project3/workspace/catkin_ws/src/map/map.yaml " &
sleep 5
xterm -e " rosrun add_markers add_markers _mode:=TEST" &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch"
