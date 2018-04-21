import socket
import sys
import pandas as pd
import pickle
class DNS:

    def __init__(self):
        self.records = pd.read_csv('records.csv')

    def query(self, domain):
        results = self.records[self.records['domain'] == domain]['ip'].values
        if results:
            return str(results[0])
        else:
            return None

dns = DNS()

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
server_address = ('localhost', 10000)
print('Starting up on host {} port {}'.format(*server_address))
sock.bind(server_address)

while True:
    print('Waiting to receive message')
    data, address = sock.recvfrom(4096)
    data = pickle.loads(data)
    print('Received {}'.format(data))

    if data:
        sent = sock.sendto(pickle.dumps(dns.query(data)), address)
