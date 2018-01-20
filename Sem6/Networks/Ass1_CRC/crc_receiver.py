# Import socket module
import socket

# Create a socket object
s = socket.socket()

# Define the port on which you want to connect
port = 9000

frames = []

s.connect(('127.0.0.1', port))
l = int(s.recv(8))
print('Got length {}'.format(l))
# s.close()
while True:
    # s.connect(('127.0.0.1', port))
    # receive data from the server
    received = s.recv(8)
    if received == '':
        break
    received = int(received)
    print('Received {}'.format(received))
    frames.append(received)

    # close the connection
    # s.close()
    l -= 1
    if l is 0:
        break
s.close()
from crc import CRC
c = CRC()
text = c.decode(frames)
print('\t\t')
print(text)
with open('output.txt', 'w') as f:
    f.write(text)
