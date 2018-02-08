import sys


class LexAnalyzer():

    def __init__(self):
        self.keywords = ['else', 'if', 'for', 'int', 'float', 'void', 'return']
        self.operators = ['+', '-', '*', '/', '<', '>', ]
        self.symbols = ['=', ';', ',', '(', ')', '{', '}']

    def _is_delim(self, c):
        if c == '\n':
            self.line_no += 1
            self.col_no = 1
            self.comment_line = False

        return c == ' ' or c == '\n' or c in self.symbols or c in self.operators

    def _is_id(self, token):
        return len(token.strip())>0 and type(token)==str

    def _is_const(self, token):
        try:
            if float(token):
                return True
            else:
                return False
        except ValueError:
            return False

    def _token_type(self, token):
        if token in self.keywords:
            return 'keyword'
        elif token in self.operators:
            return 'operator'
        elif token in self.symbols:
            return 'symbol'
        elif self._is_const(token):
            return 'const'
        elif self._is_id(token):
            return 'identifier'
        else:
            return None

    def lexical_analyzer(self, stream):
        self.line_no = 1
        self.col_no = 1
        self.comment_line = False
        output = []
        token_buffer = ''
        for idx, c in enumerate(stream):
            if self._is_delim(c):
                token_type = self._token_type(token_buffer)
                if token_buffer != '':
                    if token_type is None:
                        print('Compilation error at line_no {} col_no {} {}'.format(self.line_no, self.col_no, token_buffer))
                    else:
                        output.append((token_buffer, token_type))

                if (c==' ' or c == '\n') is False:
                    delim_type = self._token_type(c)
                    if delim_type is None:
                        print('Compilation error at line_no {} col_no {}'.format(self.line_no, self.col_no))
                    else:
                        output.append((c, delim_type))

                token_buffer = ''
            elif self.comment_line == False:
                token_buffer += c

            self.col_no += 1
        return output

if __name__ == '__main__':
    file_path = sys.argv[1] if len(sys.argv) >= 2 else input('Enter path to file$ ')
    with open(file_path, 'r') as f:
        for x in LexAnalyzer().lexical_analyzer(f.read()):
            print(x)
