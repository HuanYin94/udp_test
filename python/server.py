#!/usr/bin/env python

import serial
import rospy
import time
import socket
import string

import struct
import binascii

HOST = ''
PORT = 9999
ADDR = (HOST, PORT)

BUFFERSIZE = 1024

rospy.init_node("server")
rate = rospy.Rate(10)


server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server.bind(ADDR)

cnt = 1

while True:
	# file = open('/home/yh/test.txt', 'a')

	now = rospy.get_time()
	data_, addr_ = server.recvfrom(BUFFERSIZE)
	
	server.sendto(str(cnt), addr_)

	# data_ = struct.unpack('<L', data_)
	# data_ = string.atoi(data_)

	# data_ = ''.join([chr(i) for i in [int(b,1) for b in data_.split(' ')]])

	print addr_, '  ', data_

	cnt += 1

	# print 'received message:  ', now

	# file.write(str(data_)+"\n")
	# file.close()

	rate.sleep()

server.close()
