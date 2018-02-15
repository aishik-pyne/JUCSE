import os
import sys
import time
from crc import CRC
r_chan, w_chan = os.pipe()
r_ack, w_ack = os.pipe()
processid = os.fork()
if processid:
    # This is the parent process (receiver)
    decoder = CRC()
    os.close(w_chan)
    os.close(r_ack)
    r_chan = os.fdopen(r_chan, 'r')
    w_ack = os.fdopen(w_ack, 'w')

    print("Parent reading")
    length = r_chan.readline()[:-1]
    length = int(length)

    while length:
        c = r_chan.read()
        print(c)
        w_ack.write('1')
        length -= 1
    sys.exit(0)
else:
    # This is the child process (sender)
    encoder = CRC()
    os.close(r_chan)
    os.close(w_ack)
    w_chan = os.fdopen(w_chan, 'w')
    r_ack = os.fdopen(r_ack)
    print("Child writing")

    # Read file to send
    with open('input.txt', 'r') as f:
        text = f.read()

    # Send the length
    frames = encoder.encode(text=text, verbose=True)
    length = str(len(frames)) + '\n'
    print(length)
    os.write(w_chan, length)
    r_ack.readline()[:-1]
    print('lol')
    # Sending process
    i = 0
    while i < len(text):
        w_chan.write(text[i])
        print('lol2')
        ack = r_ack.read()
        print(ack)
        if ack == '1':
            i -= 1

    w.close()
    print("Child closing")
    sys.exit(0)
