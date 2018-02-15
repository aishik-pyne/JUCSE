import socket, sys
from crc import CRC

# Set up params
if len(sys.argv)>=2:
    port = int(sys.argv[1])
else:
    port = 8000
host = socket.gethostname()
frames = []
decoder = CRC()

# Set up socket
s = socket.socket()
s.connect((host, port))


l = int(s.recv(8).decode('utf_8'))
print(l)
print(type(l))
print('Got length {}'.format(l))
text = []
while l:

    received = s.recv(8).decode('utf_8')
    if received == '':
        break
    received = int(received)
    print('Received {}'.format(received))
    decoded_frame = decoder.decode([received], verbose=True)
    if decoded_frame != None:
        text.append(decoded_frame)
    l -= 1

s.close()

print('\t\t')
# print(text)
text = ''.join(text)
print(text)
with open('output.txt', 'w') as f:
    f.write(text)
