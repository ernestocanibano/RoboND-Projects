## SLAM
This step is to map the world which previously I created with Gazebo Building Editor. To do it we have to teleoperate manually the robot to map the environment.The simulated robot has a kinect camera and provides lase data to a gmapping package to perform a SLAM mapping of the environment.
The packages used are the following:
* `gazebo_ros`: Provides ROS plugins tha offer messages and service publishers for interfacing with Gazebo through ROS.
* `turtlebot_gazebo`: Gazebo launchers and worlds for TurtleBot simulation.
* `robot_state_publisher`: Allow to publish the state of a robot to [tf2](https://wiki.ros.org/tf2). 
* `depthimage_to_laserscan`: Takes a depth image and generates a 2D laser scan.
* `turtlebot_navigation`: Includes demos of map building using [gmapping](http://wiki.ros.org/gmapping) and localization with [amcl](http://wiki.ros.org/amcl).
* `gmapping`: Contains a ROS wrapper for OpenSlam's Gmapping. With this package is possible create a 2D occupancy grid map from laser an pose data collected by a mobile robot.
* `turtlebot_rviz_launchers`: Launchers for visualizing TurtleBot in [rviz](http://wiki.ros.org/rviz).
* `turtlebot_teleop`: Provides teleoperation of the robot using the keyboard.


## Localization & Navigation
In this case, the `gmapping` package has been replaced by the `amcl` package. This package uses the map previously generated and provides a localization service for the robot.
The packages used:
* `gazebo_ros`: Provides ROS plugins tha offer messages and service publishers for interfacing with Gazebo through ROS.
* `turtlebot_gazebo`: Gazebo launchers and worlds for TurtleBot simulation.
* `robot_state_publisher`: Allow to publish the state of a robot to [tf2](https://wiki.ros.org/tf2). 
* `depthimage_to_laserscan`: Takes a depth image and generates a 2D laser scan.
* `turtlebot_navigation`: Includes demos of map building using [gmapping](http://wiki.ros.org/gmapping) and localization with [amcl](http://wiki.ros.org/amcl).
* `amcl`: Provides a probabilistic localization system for robot in 2D. It implements the adaptative Monte Carlolocalization approach which uses a particle filter to track the pose of a robot against a known map.
* `turtlebot_rviz_launchers`: Launchers for visualizing TurtleBot in [rviz](http://wiki.ros.org/rviz).


## Home Service Robot
Based on what was implemented in the previous point,two custom packages have been developed.These two packages allow to simulate the pick up, transport and drop off of an object in the simulated world.
In addition to all the packages explained in the previous poing:
* `pick_objects`: Implements navigation through a route of two points using the ROS navigation stack. The package send goal points and orientations to the navigation stack. 
* `add_makers': Generate markers and pubish them in a topic to be seen in rviz visualization. It receives the odometry of the robot to know how to move these markers.


