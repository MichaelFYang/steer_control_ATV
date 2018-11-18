
#include "ros/ros.h"
#include "std_msgs/Float32.h"

const int num_commands = 401;

float* CommandList(){
	static float angleList[num_commands];
	int num = (num_commands-1)/4;
	for (int i=0; i<num; i++){
		angleList[i] = -2*i;
	}
	for (int i=0; i<num; i++){
		angleList[num+i] = -200 + 2*i;
	}
	for (int i=0; i<num; i++){
		angleList[2*num+i] = 2*i;
	}
	for (int i=0; i<=num; i++){
		angleList[3*num+i] = 200 - 2*i;
	}
	return angleList;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "steer_command");
	ros::NodeHandle n;
	ros::Publisher command_pub = n.advertise<std_msgs::Float32>("ros_talon/steering_angle", 100);
	ros::Rate loop_rate(5);
	float* angleList = CommandList(); 
	int count = 0;
	while (ros::ok() && count < num_commands)
	{
		std_msgs::Float32 angle_des;
		float angle = angleList[count];
		angle_des.data = angle;
		ROS_INFO("%d : %f", count, angle_des.data);
		command_pub.publish(angle_des);
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	return 0;

}
