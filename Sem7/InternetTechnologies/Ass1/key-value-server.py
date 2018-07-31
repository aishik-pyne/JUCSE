import socket

class KeyValueServer:

    def __init__(self, host='127.0.0.1', port=8000):
        # Setting up the datastructures
        self.keyvaluedict = {}

        # Setting up sockets
        self.socket = socket.socket()
        self.socket.bind((host, port)) 
        self.socket.listen(5)

    def start(self):
        try:
            while True:
                connection, client_address = self.socket.accept()     
                print('Got connection from {}', client_address)
                self.handle_connection(connection)
        except KeyboardInterrupt:
            print("Stopping Server...")
            
    def handle_connection(self, client_socket):
        req = client_socket.recv()
        print(req)
        client_socket.close()

    def _recv_req(self, connection):
        data = ""
        while True:
            buffer = connection.recv(16)
            if buffer:
                data += buffer
                print('sending data back to the client')
            else:
                print('no data')
                break

def main():
    KeyValueServer().start()

if __name__ == '__main__':
    main()