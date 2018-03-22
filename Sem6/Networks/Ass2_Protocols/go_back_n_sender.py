import os
import fcntl
import re
import psutil
import sys
import time
from collections import namedtuple
from crc import CRC
from socket import *
import pickle
from time import sleep
import threading
# Set Sent sequence number
# def seq_sent(seq_no,tempfile):
# 	fptr = open(tempfile, "r+w")
# 	fcntl.flock(fptr.fileno(),fcntl.LOCK_EX)
# 	data = fptr.readlines()
# 	if data[int(seq_no)] == seq_no + ",\n":
# 		data[int(seq_no)] = seq_no + ",W\n"
# 	new_data = ''.join(data)
# 	fptr.seek(0)
# 	fptr.truncate()
# 	fptr.write(new_data)
# 	fptr.close()


# Process to receive
def rcv_thread(soc):
	global window_size
	global total_frames
	global tempfile
	new_proc = os.fork()
	if new_proc == 0:
		print("Receive Thread " + str(os.getpid()) + " created..")
		while 1:
			while os.stat(tempfile).st_size == 0:
				continue

			status = pickle.load(open(tempfile, 'rb'))
			print(status)
			message, server_addr = soc.recvfrom(max_buff)
			message = pickle.loads(message)
			seq_no, ack = message['seq_num'], message['ack']
			print('\033[93mAck Rec {} value {}\033[0m'.format(seq_no, ack))
			if seq_no == total_frames-1:
				status['transfer_complete'] = True
				break
			if ack:
				status['window_low'] = seq_no+1
				status['window_high'] = status['window_low'] + window_size
				x = open(tempfile, 'wb')
				fcntl.flock(x, fcntl.LOCK_EX )
				pickle.dump(status, open(tempfile, 'wb') )
				fcntl.flock(x, fcntl.LOCK_UN)

def pack_data(seq_no, frame):
	return pickle.dumps({'seq_num': seq_no, 'frame':frame})

if __name__ == '__main__':
	# Set the start time
	start_time = time.time()

	# Get command line arguments
	server_host = 'localhost'
	port = int(sys.argv[1])
	send_file = sys.argv[2]
	window_size = 8
	tempfile = 'tempfile.txt'
	# Set the maximum buffer size
	max_buff = 65535

	# Setup CRC
	crc = CRC()
	data_pkt = namedtuple('data_pkt', 'seq_num frame')
	ack_pkt = namedtuple('ack_pkt', 'seq_num ack')

	# Encode the frames
	frames = crc.encode(open(send_file, 'r').read())

	# Setup global vars
	total_frames = len(frames)
	ack_recv_till = 0
	seq_no_to_send = 0
	status = {
		'transfer_complete' : False,
		'window_low' : 0,
		'window_high' : window_size -1,
	}
	pickle.dump(status, open(tempfile, 'wb'))
	# COMMS
	client_socket = socket(AF_INET,SOCK_DGRAM)

	# Thread to handle ACKS
	rcv_thread(client_socket)

	# Send file
	while 1:
		x = open(tempfile, 'rb')
		fcntl.flock(x, fcntl.LOCK_EX )
		status = pickle.load(x)
		fcntl.flock(x, fcntl.LOCK_UN)
		# print(status)
		if status['transfer_complete']:
			print( "File transfer Complete ..")
			print( "Total time in seconds : " + str(time.time() - start_time))
			break

		print('Trying to send {}'.format(seq_no_to_send))
		message_to_send = pack_data(seq_no_to_send, frames[seq_no_to_send])
		client_socket.sendto(message_to_send,(server_host,port))
		# set_timeout(send_seq_no,tempfile)
		seq_no_to_send += 1
		if seq_no_to_send > status['window_high']:
			seq_no_to_send = status['window_low']

	# Close socket
	client_socket.close()
