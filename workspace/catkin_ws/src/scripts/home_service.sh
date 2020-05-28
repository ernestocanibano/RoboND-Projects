#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find turtlebot_gazebo)/../../map/myworld.world" & 
sleep 5
xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find turtlebot_gazebo)/../../map/map.yaml " &
sleep 5
xterm -e " rosrun add_markers add_markers " &
sleep 5
xterm -e " roslaunch $(rospack find turtlebot_gazebo)/../../rvizConfig/view_navigation_custom.launch" &
sleep 5
xterm -e " rosrun pick_objects pick_objects"  
