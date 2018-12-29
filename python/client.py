#!/usr/bin/env python

import serial
import rospy
import time
import socket

HOST = '192.168.1.20'
PORT = 9999
ADDR = (HOST, PORT)

BUFFERSIZE = 1024

rospy.init_node("client")
rate = rospy.Rate(1)

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

cnt = 1
while True:

	client.sendto(str(cnt), ADDR)
	
	cnt += 1

	print str(cnt)

	rate.sleep()

client.close()
