#!/usr/bin/env python

import serial
import rospy
from tf import TransformListener
import tf
import time
import socket


rospy.init_node("trans")
# device = serial.Serial("/dev/ttyUSB1", 115200, timeout=0.1, writeTimeout=0.1)
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client.connect(("127.0.0.1", 8001))

position_old = None

listener = TransformListener()
i = 0
rate = rospy.Rate(10)
while not rospy.is_shutdown():
  try:
    t = listener.getLatestCommonTime("map", "base_footprint")
    position, quaternion = listener.lookupTransform("map", "base_footprint", t)

    msg = "lidar,%f,%f,%f,%f,%f,%f,%f\r\n" % (position[0], position[1], position[2], quaternion[3], quaternion[0], quaternion[1], quaternion[2])
	
	#print (msg)
    # msg = "%d\r\n" % i
    rospy.loginfo(msg)
    # device.write(msg)

    # i += 1
    client.sendall(msg)

    #data = client.recv(10)
    # print data
  except tf.Exception:
    print "WTF"
    time.sleep(1)
  rate.sleep()
