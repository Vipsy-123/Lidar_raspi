#!/usr/bin/env python

import rospy
from sensor_msgs.msg import LaserScan
import numpy as np
import math
import serial
import time

# Define the serial port and baud rate for communication with Arduino
serial_port = '/dev/ttyACM0'  # Replace with your Arduino's serial port
baud_rate = 9600

# Initialize the serial connection
ser = serial.Serial(serial_port, baud_rate)
time.sleep(2)  # Allow time for the Arduino to establish the serial connection

def lidar_callback(scan):
    # Access the raw lidar data
    ranges = scan.ranges
    angles = scan.angle_min
    angle_increment = scan.angle_increment
    
    min_dist=65536
    min_angle=0
    # Iterate through the range and angle data
    for i in range(len(ranges)):
        angle = angles + i * angle_increment
        distance = ranges[i]

        # Scale the angle from 0 to 360 degrees
        angle_degrees = math.degrees(angle)
        if angle_degrees < 0:
            angle_degrees += 360

        # Print angle and distance
        #print("Angle:", angle_degrees, "Distance:", distance)
        #determine the min angle
        if(distance<min_dist):
            min_dist=distance
            min_angle=angle_degrees
    
    print("MIN Angle:",min_angle,"  min dist:",min_dist)
    angle_str = str(min_angle)
    distance_str = str(min_dist)
    data = angle_str + ',' + distance_str + '\n'
    ser.write(data.encode())

def lidar_listener():
    rospy.init_node('lidar_listener', anonymous=True)
    rospy.Subscriber('/scan', LaserScan, lidar_callback)
    rospy.spin()

if __name__ == '__main__':
    lidar_listener()
