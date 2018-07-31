#!/usr/bin/python3
import pprint
pp = pprint.PrettyPrinter(indent=4)
class DFA():
    def __init__(self, states=[], symbols=[], start_state=None, final_states=[]):
        self.states = []
        self.symbols = symbols
        self.start_state = start_state
        self.final_states = final_states
        self.transitions = {}
        for s in states:
            self.add_state(s)

    def add_state(self, state):
        self.states.append(state)
        self.transitions[state] = {}

    def add_final_state(self, state):
        self.final_states.append(state)
    def add_transition(self, start, symbol, destination):
        if symbol not in self.transitions[start]:
            self.transitions[start][symbol] = destination
        else:
            print("Transition already exists")

    def print_dfa(self):
        print("\n\tDFA \n------------------------")
        print("STATES \t{}".format(self.states))
        print("SYMBOL \t{}".format(self.symbols))
        print("TRANSITIONS")
        pp.pprint(self.transitions)
        print("START STATE \t{}".format(self.start_state))
        print("FINAL STATE \t{}".format(set(self.final_states)))

    def simulate(self, string):
        current_state = self.start_state
        for idx, char in enumerate(string):
            if self.transitions[current_state]:
                if char in self.transitions[current_state]:
                    current_state = self.transitions[current_state][char]
                else:
                    return False
            else:
                return False
        if current_state in self.final_states:
            return True
        else:
            return False

class Node():

    def __init__(self, val=None, parent=None):
        self.val = val
        self.children = []
        self.parent = parent
        self.first_pos = set()
        self.last_pos = set()
        self.follow_pos= set()
        self.nullable = None

    def _isleaf(self):
        if len(self.children) == 0:
            return True
        return False

    def _uncomputed_nfl(self):
        if self.nullable == None and len(self.first_pos) == 0 and len(self.last_pos) == 0:
            return True
        return False

    def printTree(self):
        if not self._isleaf():
            if self.parent:
                parent = self.parent.val
            else:
                parent = 'root'

            print("{}\t{}\t{} \t\t nullable: {}".format(self.first_pos, self.val, self.last_pos, self.nullable))
            print("Children\t{}\n".format('\t'.join([str(x) for x in self.children])))

            for x in self.children:
                x.printTree()

    def __str__(self):
        return self.val

class ParseTree():
    def __init__(self, exp):
        self.exp = exp+'#'
        self.pos = 1
        self.leaves = {}
        self.symbols = set()
        self.root = self.parse()
        self.compulte_nfl(self.root)
        self.compulte_followpos(self.root)
        self.to_dfa()

    def _tostr(self, state):
        string = ''
        for s in sorted(list(state)):
            string += str(s) + ','
        return string

    def compulte_nfl(self, node):
        if not node._isleaf():
            for c in node.children:
                if c._uncomputed_nfl():
                    self.compulte_nfl(c)

            if node.val == '*':
                node.nullable = True
                node.first_pos = node.children[0].first_pos
                node.last_pos = node.children[0].last_pos
            elif node.val == '.':
                node.nullable = node.children[0].nullable and node.children[1].nullable
                if node.children[0].nullable:
                    node.first_pos = node.children[0].first_pos | node.children[1].first_pos
                else:
                    node.first_pos = node.children[0].first_pos

                if node.children[1].nullable:
                    node.last_pos = node.children[0].last_pos | node.children[1].last_pos
                else:
                    node.last_pos = node.children[1].last_pos
            elif node.val == '|':
                node.nullable = node.children[0].nullable or node.children[1].nullable
                node.first_pos = node.children[0].first_pos | node.children[1].first_pos
                node.last_pos = node.children[0].last_pos | node.children[1].last_pos

    def compulte_followpos(self, node):
        for c in node.children:
            if not c._isleaf():
                self.compulte_followpos(c)
        if node.val == '.':
            for i in node.children[0].last_pos:
                self.leaves[i].follow_pos |= node.children[1].first_pos
        elif node.val == '*':
            for i in node.last_pos:
                self.leaves[i].follow_pos |= node.first_pos

    def parse(self, index=0):
        node = Node()
        while self.exp[index] != '#':
            char = self.exp[index]
            if char == '(':
                newNode, index = self.parse(index+1)
                if node.parent == None:
                    node.parent = Node(None, None)
                    node.parent.children.append(node)
                newNode.parent = node.parent
                parent = node.parent
                parent.children.pop()
                parent.children.append(newNode)
                node = node.parent
            elif char == '*':
                if node.val:
                    newNode = Node('*', None)
                    newNode.children.append(node)
                    node.parent = newNode
                    node = newNode
                else:
                    node.val = '*'
                    node.parent = Node(None, None)
                    node.parent.children.append(node)
                    node=node.parent
            elif char == '.' or char == '|':
                if node.val: # asscend from right side
                    newNode = Node(char, None)
                    newNode.children.append(node)
                    node.parent = newNode
                    newNode.children.append(Node(None,newNode))
                    node = newNode.children[-1]
                else: # asscend from left side (right node doesn't exists)
                    node.val = char
                    node.children.append(Node(None, node))
                    node = node.children[-1]
                # print('operator <{}>'.format(char))
            elif char.isdigit() or char.isalpha():
                node.val = char
                self.symbols.add(char)
                node.first_pos.add(self.pos)
                node.last_pos.add(self.pos)
                self.leaves[self.pos] = node
                node.nullable = False
                self.pos += 1
                if node.parent == None:
                    newNode = Node()
                    newNode.children.append(node)
                    node.parent = newNode
                node = node.parent
                # print('token <{}>'.format(char))
            elif char == ')':
                # print(node)
                return node, index

            index +=1

        node.parent = Node('.',None)
        node.parent.children.append(node)
        node = node.parent
        node.children.append(Node('#', node))
        node.children[-1].nullable = False
        node.children[-1].first_pos.add(self.pos)
        node.children[-1].last_pos.add(self.pos)
        self.leaves[self.pos] = node
        self.final_pos = self.pos # DFA FINAL STATE

        return node

    def print_follow_pos(self):
        print("\tFOLLOW POS \n------------------------")
        print('NODE\tFOLOWPOS')
        for pos, node in self.leaves.items():
            print('{}\t{}'.format(pos,node.follow_pos))

    def print_syntax_tree(self):
        print("\tSYNTAX TREE\n------------------------")
        self.root.printTree()

    def _allmarked(self):
        for item in self.Dstates:
            if item["marked"] == False:
                return False
        return True

    def _markstate(self, state):
        for idx, item in enumerate(self.Dstates):
            if item["state"] == state:
                self.Dstates[idx]["marked"] = True

    def _stateexists(self, state):
        for item in self.Dstates:
            if item["state"] == state:
                return True
        return False

    def _getunmarkedstate(self):
        for item in self.Dstates:
            if item["marked"] == False:
                return item["state"]

    def to_dfa(self):
        self.dfa = DFA(symbols=self.symbols, start_state=self._tostr(self.root.first_pos))
        self.Dstates = [{"state":self.root.first_pos,"marked":False}]
        allmarked = False

        while not self._allmarked():
            S = self._getunmarkedstate()
            self._markstate(S)
            self.dfa.add_state(self._tostr(S))
            if self.final_pos in S:
                self.dfa.add_final_state(self._tostr(S))
            for a in self.symbols:
                U = set()
                for p in S:
                    if self.leaves[p].val == a:
                        U |= self.leaves[p].follow_pos
                if not self._stateexists(U):
                    self.Dstates.append({"state":U, "marked":False})
                self.dfa.add_transition(self._tostr(S), a, self._tostr(U))

        return self.dfa


class LexAnalyzer():

    def __init__(self):
        self.keywords = ['else', 'if', 'for', 'int', 'float', 'void', 'return', 'main']
        self.operators = ['+', '-', '*', '/', '<', '>', ]
        self.symbols = ['=', ';', ',', '(', ')', '{', '}']
        self.identifier = ParseTree('(a|b|c).(a|b|c|0|1|2)*.(a|b|c|0|1|2)').to_dfa()
        self.int = ParseTree(' (0|1|2|3|4|5|6|7|8|9)*.(0|1|2|3|4|5|6|7|8|9)').to_dfa()
        self.float = ParseTree(' (0|1|2|3|4|5|6|7|8|9)*.(0|1|2|3|4|5|6|7|8|9)').to_dfa()
        ParseTree(' (0|1|2|3|4|5|6|7|8|9)*.(0|1|2|3|4|5|6|7|8|9)').print_syntax_tree()
        self.int.print_dfa()

    def _is_delim(self, c):
        if c == '\n':
            self.line_no += 1
            self.col_no = 1
            self.comment_line = False

        return c == ' ' or c == '\n' or c in self.symbols or c in self.operators

    def _is_id(self, token):
        return self.identifier.simulate(token)

    def _is_int(self, token):
        return self.int.simulate(token)


    def _is_float(self, token):
        return self.float.simulate(token)

    def _token_type(self, token):
        if token in self.keywords:
            return 'keyword'
        elif token in self.operators:
            return 'operator'
        elif token in self.symbols:
            return 'symbol'
        elif self._is_int(token):
            return 'Integer'
        elif self._is_float(token):
            return 'Float'
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
                # print(token_buffer)
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
    # d = DFA(['123','1234','1235','1236'], ['a', 'b'], '123', ['1236'])
    # d.add_transition('123','a','1234')
    # d.add_transition('123','b','123')
    # d.add_transition('1234','a','1234')
    # d.add_transition('1234','b','1235')
    # d.add_transition('1235','a','1234')
    # d.add_transition('1235','b','1236')
    # d.add_transition('1236','a','123')
    #
    # pp.pprint(d.transitions)
    # print(d.simulate('cc'))

    p = ParseTree('(a|b)*.a.b.b')
    p.print_syntax_tree()
    p.print_follow_pos()
    dfa = p.to_dfa()
    dfa.print_dfa()
    print(dfa.simulate('ababb'))

    # IF = ParseTree('i.f')
    # FOR = ParseTree('f.o.r')
    # INT = ParseTree('(0|1|2|3|4|5|6|7|8|9)*.(0|1|2|3|4|5|6|7|8|9)')
    # INT.print_syntax_tree()
    # INT.to_dfa().print_dfa()
    for x in LexAnalyzer().lexical_analyzer(open('input.c', 'r').read()):
        print(x)
