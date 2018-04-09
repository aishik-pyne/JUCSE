class DFA():
    def __init__(self, states=[], symbols=[], start_state=None, final_states=[]):
        self.states = states
        self.symbols = symbols
        self.start_state = start_state
        self.final_states = final_states
        self.transitions = [{s:None for s in self.symbols} for _ in self.states]
        print(self.transitions)

    def add_transition(self, start, symbol, destination):
        if not self.transitions[start][symbol]:
            self.transitions[start][symbol] = destination
        else:
            print("Transition already exists")

    def simulate(self, string):
        current_state = self.start_state
        for idx, char in enumerate(string):
            if self.transitions[current_state][char]:
                current_state = self.transitions[current_state][char]
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
        if True:#not self._isleaf():
            if self.parent:
                parent = self.parent.val
            else:
                parent = 'root'
            print('Parent:{} \tNode: {} \nfirst_pos: {} \tlast_pos: {} \tnullable: {}'.format(parent, self.val, self.first_pos, self.last_pos, self.nullable))
            print('Follow Pos: {}'.format(self.follow_pos))
            print('Children: {}\n'.format([x.val for x in self.children]))

            for x in self.children:
                x.printTree()

class ParseTree():
    def __init__(self, exp):
        self.exp = exp+'#'
        self.pos = 1
        self.leaves = {}
        self.root = self.parse()
        self.compulte_nfl(self.root)
        self.compulte_followpos(self.root)

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
                self.leaves[i].follow_pos |= node.children[0].first_pos
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

        return node

    def print_follow_pos(self):
        print('NODE\tFOLOWPOS')
        for pos, node in self.leaves.items():
            print('{}\t{}'.format(pos,node.follow_pos))

    def print_syntax_tree(self):
        pass
if __name__ == '__main__':
    # d = DFA([0,1,2,3], ['a', 'b', 'c'], 0, [3])
    # d.add_transition(1,'a',2)
    # d.add_transition(1,'b',3)
    # d.add_transition(2,'c',3)
    # d.add_transition(0,'c',2)
    #
    # print(d.simulate('ccccc'))
    p = ParseTree('(a|b)*.a.a.b')
    p.root.printTree()
    p.print_follow_pos()
