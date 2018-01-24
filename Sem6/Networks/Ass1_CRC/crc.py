class CRC():
    """docstring for CRC."""
    def __init__(self, poly=11, frame_size=3):
        self.poly = poly if type(poly) is int else int(poly, 2)

        self.frame_size = frame_size

    def __repr__(self):
        return '<crc encoder with poly {0:b} and frame_size {1}>'.format(self.poly, self.frame_size)

    def _to_bytes(self, text):
        '''Returns a list of ASCII values of each char in string'''
        assert type(text) is str
        return [ord(x) for x in text]

    def _pad(self, text):
        '''Retuns a padded text such that len(text) is multiple of frame_size'''
        assert type(text) is str
        for _ in range(self.frame_size-(len(text)%self.frame_size)):
            text += ' '
        return text

    def _concat_bytes(self, frame):
        x = 0
        for b in frame if type(frame) is list else [frame]:
            x = (x<<8) | b
        return x

    def _deconcat_bytes(self, frame):
        x = []
        while frame:
            x.append(frame & 255)
            frame = frame >> 8
        return x[::-1]

    def _code(self, frame):
        '''
        For internal use
        Returns crc code the frame
        '''
        self.poly_len = len(format(self.poly, 'b'))
        # Build the divisor from the frame elements
        divident = self._concat_bytes(frame)

        # Append trailing 0's
        divident = divident<<(self.poly_len-1)

        # Compute the remainder
        while len(format(divident, 'b')) >= self.poly_len:
            divisor = self.poly << (len(format(divident, 'b'))-self.poly_len)
            divident = divident ^ divisor

        return divident

    def _corrupt_frame(self, frame):
        from random import randrange
        pos = randrange(0, len(frame))
        if frame[pos] = 0:
            return text[:pos] + '1' + text[pos+1:]
        else:
            return text[:pos] + '0' + text[pos+1:]

    def encode(self, text='', verbose=False):
        if verbose:
            print('\n\t\tENCODING\n')
        text = self._pad(text)
        bytetext = self._to_bytes(text)
        rframes = []
        for idx in range(0, len(bytetext)-1, self.frame_size):
            # Building the Frame
            frame = [bytetext[j] for j in range(idx, idx+self.frame_size)]
            code = self._code(frame)
            rframe = (self._concat_bytes(frame) << (self.poly_len-1)) ^ code
            rframes.append(rframe)
            if verbose:
                print('Frame {0:03}  Str {1} \t Data {2}  CRC {3:05b}'.format(idx, repr(text[idx:idx+self.frame_size]), ["{0:08b}".format(x) for x in (frame)], code))

        return rframes

    def decode(self, frames=[], verbose=False):
        if verbose:
            print('\n\t\tDECODING\n')
        text = ''
        for idx, f in enumerate(frames):
            if self._code(f) != 0:
                print('Frame no.{0} is corrupted. corrupted value: {1:b}'.format(idx, f))
                return None
            else:
                # Discard the redundency
                f = f>>(self.poly_len-1)
                # Decompose the frame
                text += ''.join([chr(x) for x in self._deconcat_bytes(f)])
                if verbose:
                    print('Frame {0:03} Data {1:b} \t Str {2}'.format(idx, f, repr(''.join([chr(x) for x in self._deconcat_bytes(f)])) ))

        return text.strip()


# with open('input.txt', 'r') as f:
#     text = f.read()
#
# c = CRC(frame_size=5)
# frames = c.encode(text, verbose=True)
# print(c.decode(frames=frames, verbose=True))
