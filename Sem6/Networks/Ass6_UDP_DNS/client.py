#!/usr/bin/python3
import socket
import sys
import pickle

if len(sys.argv) >= 2:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = ('localhost', 10000)
    try:
        for i in range(1, len(sys.argv)):
            domain = sys.argv[i]
            # Send data
            print('Sending {}'.format(domain))
            sent = sock.sendto(pickle.dumps(domain), server_address)

            # Receive response
            print('Waiting for response...')
            data, server = sock.recvfrom(4096)
            print('Received {}'.format(pickle.loads(data)))

    finally:
        print('Closing socket')
        sock.close()
else:
    print('Atleast one arg is reqd')
