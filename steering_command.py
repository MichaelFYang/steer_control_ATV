#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float32

def steer_command(command_list):
	pub = rospy.Publisher('ros_talon/steering_angle', Float32, queue_size=10)
	rospy.init_node('steer_command', anonymous=True)
	rate = rospy.Rate(1) # 10hz
	timeIndex = 0
	while not rospy.is_shutdown():
		angle_command = command_list[timeIndex]
		timeIndex += 1
		rospy.loginfo(angle_command)
		pub.publish(angle_command)
		rate.sleep()

if __name__ == '__main__':
	try:
		command_list = [0,50,100,50,0,-50,-100,-50,0]
		steer_command(command_list)
	except rospy.ROSInterruptException:
		pass