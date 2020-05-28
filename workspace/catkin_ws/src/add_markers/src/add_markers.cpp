#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

const float pickup_x = 5.06;
const float pickup_y = -1.49;
const float dropoff_x = -8.38;
const float dropoff_y = 2.83;
const float threshold = 0.5; 

enum status {
    TEST = 0,
    PICKUP = 1,
    DROPOFF = 2,
    UNKNOWN = 4,
};

status markerStatus = UNKNOWN;

visualization_msgs::Marker marker;
ros::Publisher marker_pub;

// This callback function receives the odometry data
void odom_callback(const nav_msgs::Odometry::ConstPtr &msg)
{
  float dist = 0.0;

  // get the x,y coordinates of the robot
  float x = msg->pose.pose.position.x;
  float y = msg->pose.pose.position.y;

  switch(markerStatus){
    case PICKUP:
      dist = sqrt(pow(x-dropoff_x,2) + pow(y-dropoff_y,2));
      ROS_INFO("Distance to drop off location: %f", dist);

      if(dist <= threshold){
         // Delete marker at pickup location
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = dropoff_x;
        marker.pose.position.y = dropoff_y;
        marker_pub.publish(marker);
        ROS_INFO("Show marker at drop off location"); 
        markerStatus = DROPOFF;
      }
      break;
    case DROPOFF:
      ROS_INFO("All task ended");
      break;
    default:
      dist = sqrt(pow(x-pickup_x,2) + pow(y-pickup_y,2));
      ROS_INFO("Distance to pickup location: %f", dist);

      if(dist <= threshold){
         // Delete marker at pickup location
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        ROS_INFO("Delete marker at pickup location"); 
        markerStatus = PICKUP;
      }
  }
  
    
}

int main( int argc, char** argv )
{
  std::string param;

  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n("~");
  ros::Rate r(1);
  n.getParam("mode", param);

  if(param.compare("TEST") == 0)
  {
    ROS_WARN("Working on test mode");
    markerStatus = TEST;
  }       


  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Subscribe to odom topic to read the robot position
  ros::Subscriber sub = n.subscribe("/odom", 1000, odom_callback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
 
    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;
 
    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
 
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;
 
    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0.0;
    marker.pose.position.y = 0.0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;
 
    marker.lifetime = ros::Duration();
 
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    
    //show marker at pickup location
    marker.pose.position.x = pickup_x;
    marker.pose.position.y = pickup_y;
    marker_pub.publish(marker);
    ROS_INFO("Show marker at pickup location");

    if(markerStatus != TEST){
      // Handle ROS communication events
      ros::spin();
    }else{

      ros::Duration(5.0).sleep();

      // Delete marker at pickup location
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      ROS_INFO("Delete marker at pickup location");
      ros::Duration(5.0).sleep();


      // Show marker at drop off location
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = dropoff_x;
      marker.pose.position.y = dropoff_y;
      marker_pub.publish(marker);
      ROS_INFO("Show marker at drop off location");
    }
    return 0;
  }
 }