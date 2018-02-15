from crc import CRC
import sys, socket
from random import randrange
class StopAndWait():
    '''
    Paramters
    - user : sender/receiver mode
    - crc  : crc scheme. Defaults to default CRC
    - host : host
    - port : port

    Usage
    - sender mode : Sends a frame and waits for sometime for ack.
                    If false ack or timeout, resend the frame
    - receiver mode : Receives frame. Check if it is correct.
                        Sends ack
    '''
    def __init__(self, user='sender', crc=None, host=socket.gethostname(), port=8000):
        if crc == None:
            crc = CRC()
        self.crc = crc # This will act as a decoder and encoder for the protocol
        self.user = user

        self._init_socket(host, port)
        self.host = host
        self.port = port
    def _init_socket(self, host, port):
        if self.user == 'sender':
            self.socket = socket.socket()
            self.socket.bind((host, port))
<<<<<<< HEAD
            self.socket.listen(1)
        elif self.user == 'receiver':
            self.socket = socket.socket()

        else:
            raise ValueError('Incorrect user mode')

    def _send_one_frame(self, frame, conn, corrupt_simulation=False):
        # Put in corruptions
        if randrange(0,10) <=2 and corrupt_simulation:
            frame = self.crc._corrupt_frame(frame)
        conn.sendall(str(frame).zfill(8).encode('utf-8'))
        # conn.flush()
        print('{} sent'.format(str(frame).zfill(8)))

    def _receive_ack(self, conn):
        print('waiting for ack')
        ack = int(conn.recv(1))
        print('Received ack {}'.format(True if ack == 1 else False))
        if ack == 1:
            return True
        else:
            return False

    def send(self, text, corrupt_simulation=True, verbose=False):
        frames = self.crc.encode(text=text, verbose=True)
        c, addr = self.socket.accept()
=======
            self.socket.listen(5)
    def _send_one_frame(self, frame):
        pass

    def _receive_ack(self):
        pass

    def send(self, text, verbose=False):
        frames = self.crc.encode(text=text)
        c, addr = s.accept()
        c.sendall(msglen.encode('utf-8'))
>>>>>>> 0ca10807915fb1c10f2c6459b2ac6cdfcd51234a
        for f in frames:
            self._send_one_frame(f, conn=c, corrupt_simulation=corrupt_simulation)
            while not self._receive_ack(conn=c):
                self._send_one_frame(f, conn=c)
        c.close()
<<<<<<< HEAD


    def _receive_one_frame(self):
        frame = self.socket.recv(8).decode('utf_8')
        print('Frame {} received'.format(frame))
        if frame:
            return int(frame)
        return None

    def _send_ack(self, ack):
        if ack:
            self.socket.send('1'.encode('utf-8'))
        else:
            self.socket.send('0'.encode('utf-8'))
        print('Ack sent {}'.format(ack))

    def receive(self):
        text = ''
        self.socket.connect((self.host, self.port))
        while True:

            frame = self._receive_one_frame()
            if frame == None:
                break
            decoded_frame = self.crc.decode([frame])
            if decoded_frame != None:
                self._send_ack(True)
                text += decoded_frame
            else:
                 self._send_ack(False)
=======
>>>>>>> 0ca10807915fb1c10f2c6459b2ac6cdfcd51234a


        self.socket.close()
        return text

if __name__ == '__main__':
    if len(sys.argv) >1:
        user = sys.argv[1]
    else:
        user = input('Sender or Receiver')

    if len(sys.argv) >2:
        port = int(sys.argv[2])
    else:
        port = 8000

    print('Simulating StopAndWait Protocol for {}'.format(user))
<<<<<<< HEAD
    saw = StopAndWait(user=user, port=port)
    if user == 'sender':
        with open('input.txt') as f:
            text = f.read()
        saw.send(text)
    elif user == 'receiver':
        print(saw.receive())
=======
    with open('input.txt') as f:
>>>>>>> 0ca10807915fb1c10f2c6459b2ac6cdfcd51234a
