# first of all import the socket library
import socket, sys
from sys import getsizeof
from crc import CRC
from random import randrange
encoder = CRC()
s = socket.socket()
print("Socket successfully created")

if len(sys.argv)>=2:
    port = int(sys.argv[1])
else:
    port = 8000
host = socket.gethostname()

s.bind((host, port))
print("socket binded to {}".format(port))
# put the socket into listening mode
s.listen(5)
print("socket is listening")

# Read input text
with open('input.txt', 'r') as f:
    text = f.read()
    frames = encoder.encode(text, verbose=True)
    msglen = str(len(frames)).zfill(8)
    print(getsizeof(frames))
c, addr = s.accept()



c.sendall(msglen.encode('utf-8'))
for f in frames:
    if randrange(0,10) <=2:
        f = encoder._corrupt_frame(f)
    c.sendall(str(f).zfill(8).encode('utf-8'))
    print('{} sent'.format(str(f).zfill(8)))
c.close()
