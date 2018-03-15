from crc import CRC
import sys, socket
from random import randrange
import pickle

data_pkt = namedtuple('data_pkt', 'seq_num frame')
ack_pkt = namedtuple('ack_pkt', 'seq_num ack')

class GoBackNSender():
    '''
    Paramters
    - crc  : crc scheme. Defaults to default CRC
    - host : host
    - port : port

    '''
    def __init__(self, crc=None,
                host=socket.gethostname(), port=8000
                window_size=8):
        self.crc = crc if crc not None else CRC()
        self._init_socket(host, port)
        self.host = host
        self.port = port

    def _init_socket(self, host, port):
        self.socket = socket.socket()
        self.socket.bind((host, port))
        self.socket.listen(1)

    def _send_one_frame(self, frame, conn, corrupt_simulation=False):
        # Put in corruptions
        if randrange(0,10) <=2 and corrupt_simulation:
            frame = self.crc._corrupt_frame(frame)
        conn.sendall(str(frame).zfill(8).encode('utf-8'))
        # conn.flush()
        print('{} sent'.format(str(frame).zfill(8)))

    def _receive_ack_thread(self, conn):
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
        for f in frames:
            self._send_one_frame(f, conn=c, corrupt_simulation=corrupt_simulation)
            while not self._receive_ack(conn=c):
                self._send_one_frame(f, conn=c)
        c.close()



class GoBackNReceiver():
    def __init__(self, crc=None,
                host=socket.gethostname(), port=8000,
                window_size=8, drop_prob=0.1):
        if crc == None:
            crc = CRC()
        self.crc = crc # This will act as a decoder and encoder for the protocol

        self._init_socket(host, port)
        self.host = host
        self.port = port
        self.window_size = window_size

    def _init_socket(self, host, port):
        self.socket = socket.socket()
        self.exp_seq_num = 0

    def _send_ack(self, seq_num, ack):
        self.socket.send(pickle.dumps(ack_pkt(seq_num, ack)))
        print('Ack sent seq_num {} ack {}'.format(seq_num, ack))

    def _receive_one_frame(self):
        data = pickle.loads(self.socket.recv(64))
        seq_num, frame = data.seq_num, data.frame
        print('Frame seq_num {} received {}'.format(seq_num, frame))
        if frame:
            return seq_num, int(frame)
        return seq_num, None

    def receive(self):
        text = ''
        self.socket.connect((self.host, self.port))
        while True:
            seq_num, frame = self._receive_one_frame()
            if frame == None:
                break
            decoded_frame = self.crc.decode([frame])
            if decoded_frame != None:
                self._send_ack(seq_num, True)
                text += decoded_frame
            else:
                 self._send_ack(seq_num, False)


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
    saw = StopAndWait(user=user, port=port)
    if user == 'sender':
        with open('input.txt') as f:
            text = f.read()
        saw.send(text)
    elif user == 'receiver':
        print(saw.receive())
