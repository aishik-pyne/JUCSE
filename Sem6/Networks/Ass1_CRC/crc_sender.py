# first of all import the socket library
import socket

# next create a socket object
s = socket.socket()
print("Socket successfully created")

# reserve a port on your computer in our
# case it is 12345 but it can be anything
port = 9000

# Next bind to the port
# we have not typed any ip in the ip field
# instead we have inputted an empty string
# this makes the server listen to requests
# coming from other computers on the network
s.bind(('localhost', port))
print("socket binded to {}".format(port))

# put the socket into listening mode
s.listen(5)
print("socket is listening")

# a forever loop until we interrupt it or
# an error occurs
with open('input.txt', 'r') as f:
    text = f.read()
from crc import CRC
c = CRC()
frames = c.encode(text)
c, addr = s.accept()
c.send(str(len(frames)).zfill(8))

# c.close()
for f in frames:
   # Establish connection with client.
   # c, addr = s.accept()
   # print(( 'Got connection from', addr))

   # send a thank you message to the client.
   c.send(str(f))
   print('{} sent'.format(f))

   # Close the connection with the client
c.close()
