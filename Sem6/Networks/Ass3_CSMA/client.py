#!/usr/bin/python3
import socket
import sys
import pickle
from time import sleep
import threading

class Receive(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.name = "receive"
        self.alive = True

    def stop(self):
        self.alive = False

    def run(self):
        while self.alive:
            response, server = sock.recvfrom(4096)
            response = pickle.loads(response)
            # print(response)
            if response["response"] == "data" and response["to"] == username:
                print("\n{}: {}".format(response["from"], response["data"]))


class Sender(threading.Thread):
    def __init__(self, server_address):
        threading.Thread.__init__(self)
        self.server_address = server_address
        self.name = "sender"
        self.alive = True

    def stop(self):
        self.alive = False

    def run(self):
        tempSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        while self.alive:
            to = str(input("To: "))
            msg = str(input("Data: "))
            backoff = 1
            while True:
                tempSock.sendto(pickle.dumps({"type":"isbusy"}), self.server_address)
                response, server = tempSock.recvfrom(4096)
                response = pickle.loads(response)
                # print(response)
                if response["response"] == "ready":
                    print("Transmitting Data")
                    # Channel busy delay. Comment it for real time

                    sleep(5)
                    # Send data
                    tempSock.sendto(pickle.dumps({"type":"data", "data":msg, "to":to, "from":username}), self.server_address)
                    print("Packet delivered")
                    break
                elif response["response"] == "busy":
                    print("Backing off for {}s".format(backoff))
                    sleep(backoff)
                    backoff = backoff * 2 # exponetial backoff
                    if backoff == 64:
                        print("Packet died. Try again later")
                        break
        tempSock.close()


if len(sys.argv) == 2:
    username = str(sys.argv[1])
    print("Welcome {}".format(username))
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('localhost', 10000)
    lock = threading.RLock()
    send_thread = Sender(server_address)
    receive_thread = Receive()
    try:
        # Connect
        while True:
            sock.sendto(pickle.dumps({"type":"connect"}), server_address)
            response, sender_address = sock.recvfrom(4096)
            if pickle.loads(response)["response"] == "connected":
                print("Connected to network...")
                break

        send_thread.start()
        receive_thread.start()
    except KeyboardInterrupt:
        # Disconnect
        print("Killing Thread")
        while True:
            sock.sendto(pickle.dumps({"type":"close"}), server_address)
            response, sender_address = sock.recvfrom(4096)
            if pickle.loads(response)["response"] == "disconnected":
                print("Disconnected to network...")
                break
        send_thread.stop()
        receive_thread.stop()
    finally:
        send_thread.join()
        receive_thread.join()
        print('Closing socket')
        sock.close()
else:
    print('One arg is reqd')
