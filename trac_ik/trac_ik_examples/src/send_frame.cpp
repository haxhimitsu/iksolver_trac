#include <kdl/chain.hpp>
#include <kdl/chainfksolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainiksolverpos_nr_jl.hpp>
#include <kdl/frames_io.hpp>

#include <trac_ik/trac_ik.hpp>

#include <stdio.h>
#include <iostream>

 #include <ros/ros.h>
 #include <sensor_msgs/JointState.h>
 #include <std_msgs/Header.h>
 #include <trajectory_msgs/JointTrajectory.h>
 #include <geometry_msgs/PoseStamped.h>
 #include <sensor_msgs/Joy.h>
 #include <geometry_msgs/Pose.h>

 #include <tf/transform_broadcaster.h>


class Frame_pub{

    public:
    Frame_pub();
    void frame_pub();
    void callback(const sensor_msgs::Joy::ConstPtr& data);
    geometry_msgs::PoseStamped pos;
  private:
    ros::NodeHandle nh;
    ros::Subscriber sub;
    ros::Publisher pub;
    geometry_msgs::Pose joy_pose;

     };

Frame_pub::Frame_pub()

{   sub = nh.subscribe("joy", 10, &Frame_pub::callback,this);
    pub = nh.advertise<geometry_msgs::PoseStamped>("/end_effector_pose", 1);
    pos.pose.position.x=0.564;
    pos.pose.position.y=0.028;
    pos.pose.position.z=0.611;
    
}

void Frame_pub::frame_pub() {
    
    pos.header.frame_id="base_link";
    pos.pose.position.x=pos.pose.position.x+joy_pose.position.x;
    pos.pose.position.y=pos.pose.position.y+joy_pose.position.y;
    pos.pose.position.z = pos.pose.position.z+joy_pose.position.z;
    pos.pose.orientation.x= 0;
    pos.pose.orientation.y= 0.0001904047369388022;
    pos.pose.orientation.z= 0;
    pos.pose.orientation.w= 1.0;

    pub.publish(pos);
  }

void Frame_pub::callback(const sensor_msgs::Joy::ConstPtr& data){
    // if (data->axes[7]<0){
    // joy_pose.position.z=joy_pose.position.z-0.001;
    // }
    // else if(data->axes[7]>0){
    //      joy_pose.position.z=joy_pose.position.z+0.001;
    // }
    // else{
    //      joy_pose.position.z=joy_pose.position.z;
    // }
    joy_pose.position.z= data->axes[1]*0.0002;
    joy_pose.position.x= (-1.0*data->axes[0])*0.0002;
    joy_pose.position.y= (-1.0*data->axes[3])*0.0002;
}

int main( int argc, char** argv )
{

ros::init(argc, argv, "my_frame_publisher");

Frame_pub my1;

  ros::Rate loop_rate(500);
  while (ros::ok())
  { 
      my1.frame_pub();
    ros::spinOnce();
    loop_rate.sleep();
  }

}



// #include <ros/ros.h>
// #include <std_msgs/String.h>

// class RosWithClass{
// 	private:
// 		ros::NodeHandle nh;
// 		ros::Publisher pub;
// 		ros::Subscriber sub;
// 		std_msgs::String pub_msg;
// 	public:
// 		RosWithClass();
// 		void Publication(void);
// 		void Callback(const std_msgs::String::ConstPtr& msg);
// };

// RosWithClass::RosWithClass()
// {
// 	pub = nh.advertise<std_msgs::String>("/pub_msg", 1);
// 	sub = nh.subscribe("/message", 1, &RosWithClass::Callback, this);
// }

// void RosWithClass::Publication(void)
// {
// 	pub_msg.data = "message";
// 	pub.publish(pub_msg);
// }

// void RosWithClass::Callback(const std_msgs::String::ConstPtr& msg)
// {
// 	std::cout << msg->data.c_str() << std::endl;
// }

// int main(int argc, char**argv)
// {
// 	ros::init(argc, argv, "talker");
	
// 	RosWithClass ros_with_class;

// 	ros::Rate loop_rate(10);
// 	while(ros::ok()){
// 		ros_with_class.Publication();
// 		ros::spinOnce();
// 		loop_rate.sleep();
// 	}
// }