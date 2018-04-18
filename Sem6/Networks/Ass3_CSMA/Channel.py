#!/usr/bin/python3
import socket
import sys
import pickle

class Users:
    def __init__(self):
        self.users = []

    def add_user(self, address):
        self.users.append(address)

    def del_user(self, address):
        self.user.remove(address)


users = Users()
# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
server_address = ('localhost', 10000)
print('Starting up on host {} port {}'.format(*server_address))
sock.bind(server_address)


while True:
    packet, address = sock.recvfrom(4096)
    packet = pickle.loads(packet)
    if packet["type"] == "connect":
        users.add_user(address)
        sock.sendto(pickle.dumps({"response":"connected"}), address)
        print("User added {}".format(address))
    elif packet["type"] == "close":
        users.dek_user(address)
        sock.sendto(pickle.dumps({"response":"disconnected"}), address)
        print("User removed {}".format(address))
    elif packet["type"] == "isbusy":
        sock.sendto(pickle.dumps({"response":"ready"}), address)
        print("Channel ready for {}".format(address))

        while True: # Channel busy
            data_packet, sender_address = sock.recvfrom(4096)
            data_packet = pickle.loads(data_packet)
            if address == sender_address and data_packet["type"] == "data":
                for u in users.users: # Broadcasting message
                    if u != sender_address: # Don't send back to sender
                        sock.sendto(pickle.dumps({"response":"data", "data":data_packet["data"], "to":data_packet["to"], "from":data_packet["from"]}), u)

                break
            else:
                sock.sendto(pickle.dumps({"response":"busy"}), sender_address)
        print("Channel free")
    else:
        sock.sendto(pickle.dumps({"response":"discarded"}), address)
