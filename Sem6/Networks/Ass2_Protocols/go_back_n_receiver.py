from socket import *
from decimal import *
import os
from random import random
import time
import sys
from crc import CRC
from collections import namedtuple
import pickle

# Method to send to client
def rdt_send(got_seq_no):
	return pickle.dumps({'seq_num':got_seq_no, 'ack':True})

# Write to File
def f_write(decoded,f_name):
	with open(f_name, 'a') as f:
		f.write(decoded)

if __name__ == '__main__':
	# Collect CLI arguments
	port = int(sys.argv[1])
	output_file = sys.argv[2]
	probability = float(sys.argv[3])
	hostname = ""

	# Setup CRC
	crc = CRC()
	# data_pkt = namedtuple('data_pkt', 'seq_num frame')
	# ack_pkt = namedtuple('ack_pkt', 'seq_num ack')

	# Communication
	s = socket(AF_INET,SOCK_DGRAM)
	s.bind((hostname,port))
	print ("Listening for client requests ... ")
	exp_seq_no = 0
	while 1:
		msg, client_address = s.recvfrom(65535)
		data = pickle.loads(msg)
		got_seq_no, frame = data['seq_num'], data['frame']
		print('Packet Recv seq_no {} '.format(got_seq_no))
		if random() < probability: # Random packet drop simulation
			decoded = crc.decode([frame], verbose=True)
			if decoded is not None: # Checksum is correct
				if got_seq_no == exp_seq_no: # Send ack
					to_send = rdt_send(got_seq_no)
					if to_send:
						s.sendto(to_send, client_address)
						f_write(decoded,output_file)
						exp_seq_no = exp_seq_no + 1
				elif got_seq_no > exp_seq_no: # Future packet received, hence dropped
					print ("Packet loss, sequence number = " + str(got_seq_no))
				elif got_seq_no < exp_seq_no: # Repeat sent
					to_send = rdt_send(exp_seq_no)
					if to_send:
					# print ("Retransmitted ACK - " + str(got_seq_no))
						s.sendto(to_send, client_address)
			else:
				print ("Checksum invalid. Packet dropped.")
		else: # Random packet drop simulation
			print ("Packet loss, sequence number = " + str(got_seq_no))

	s.close()
