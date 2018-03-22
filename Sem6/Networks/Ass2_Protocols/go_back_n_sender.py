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
	global window_low
	global window_high
	global total_frames
	new_proc = os.fork()
	if new_proc == 0:
		print("Receive Thread " + str(os.getpid()) + " created..")
		while 1:
			message, server_addr = soc.recvfrom(max_buff)
			message = pickle.loads(message)
			seq_no, ack = message['seq_no'], message['ack']
			if seq_no == total_frames-1:
				transfer_complete = True
				break
			if ack:
				window_low = seq_no+1
				window_high = window_low + window_size


# # Timers
# def set_timeout(send_seq_no,tempfile):
# 	child_process = os.fork()
# 	if child_process == 0:
# 		p = psutil.Process(os.getpid())
# 		time.sleep(0.5)
# 		fptr = open(tempfile,'r+w')
# 		fcntl.flock(fptr.fileno(),fcntl.LOCK_EX)
# 		update_seq_status = -1
# 		data = fptr.readlines()
# 		for line in data:
# 			match = re.findall('(\d+),(\w)\n',line)
# 			if match:
# 				if send_seq_no == str(match[0][0]):
# 					if str(match[0][1]) == 'C':
# 						break
# 					elif str(match[0][1]) == 'W':
# 						print( "Timeout, sequence number =:" + send_seq_no)
# 						update_seq_status = 1
# 						break
# 					else:
# 						break
# 		if update_seq_status == 1:
# 			if data[int(send_seq_no)] == send_seq_no + ",W\n":
# 				data[int(send_seq_no)] = send_seq_no + ",\n"
# 			new_data = ''.join(data)
# 			fptr.seek(0)
# 			fptr.truncate()
# 			fptr.write(new_data)
# 		fptr.close()
# 		os._exit(0)
#

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
	transfer_complete = False
	window_low = 0
	window_high = window_size -1

	# COMMS
	client_socket = socket(AF_INET,SOCK_DGRAM)

	# Thread to handle ACKS
	rcv_thread(client_socket)

	# Send file
	while 1:
		if transfer_complete:
			print( "File transfer Complete ..")
			print( "Total time in seconds : " + str(time.time() - start_time))
			break

		message_to_send = pack_data(seq_no_to_send, frames[seq_no_to_send])
		client_socket.sendto(message_to_send,(server_host,port))
		# set_timeout(send_seq_no,tempfile)
		seq_no_to_send += 1
		if seq_no_to_send > window_high:
			seq_no_to_send = window_low

	# Close socket
	client_socket.close()
