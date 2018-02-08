from crc import CRC
import sys, socket

class StopAndWait():

    def __init__(self, user='sender', crc=None, host=socket.gethostname(), port=8000):
        if crc == None:
            crc = CRC()
        self.crc = crc # This will act as a decoder and encoder for the protocol
        self.user = user

        self._init_socket(host, port)

    def _init_socket(self, host, port):
        if self.user == 'student':
            self.socket = socket.socket()
            self.socket.bind((host, port))
            self.socket.listen(5)
    def _send_one_frame(self, frame):
        pass

    def _receive_ack(self):
        pass
        
    def send(self, text, verbose=False):
        frames = self.crc.encode(text=text)
        c, addr = s.accept()
        c.sendall(msglen.encode('utf-8'))
        for f in frames:
            if randrange(0,10) <=2:
                f = encoder._corrupt_frame(f)
            c.sendall(str(f).zfill(8).encode('utf-8'))
            print('{} sent'.format(str(f).zfill(8)))
        c.close()




if __name__ == '__main__':
    if len(sys.argv) >1:
        user = sys.argv[1]
    else:
        user = input('Sender of Receiver')

    print('Simulating StopAndWait Protocol for {}'.format(user))
    with open('input.txt') as f:
        text = f.read()

    saw = StopAndWait()
    saw.send(text)
