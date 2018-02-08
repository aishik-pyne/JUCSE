from crc import CRC
import sys
class StopAndWait:

    def __init__(crc = CRC()):
        self.crc = crc # This will act as a decoder and encoder for the protocol

    def send(text, verbose=False):
        frames = self.crc.encode(text=text)
        print(frames)




if __name__ == '__main__':
    if len(sys.argv) >1:
        user = sys.argv[1]
    else:
        user = input('Sender of Receiver')

    print('Simulating StopAndWait Protocol for {}'.format(user))
    with open('input.txt') as f:
        text =
