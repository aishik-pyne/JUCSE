#!/usr/bin/python3
import socket
import json


class KeyValueServer:

    def __init__(self, host='127.0.0.1', port=8000):
        # Setting up the datastructures
        self.keyvaluedict = {}

        # Setting up sockets
        self.socket = socket.socket()
        self.socket.bind((host, port))
        self.socket.listen(5)
        print("Server started on host {} port {}".format(host, port))

    def _recv_req(self, connection):
        data = ""
        while True:
            buffer = connection.recv(16)
            if buffer:
                data += buffer.decode('utf-8')
                print(data)
            else:
                break
        print(data)
        return json.loads(data)

    def _send_res(self, connection, data, status=200):
        response = json.dumps({
            "status": int(status),
            "body": data
        }).encode('utf-8')
        connection.sendall(response)

    def start(self):
        try:
            while True:
                connection, client_address = self.socket.accept()
                connection.setblocking(1)
                print('Got connection from {}', client_address)
                self.handle_connection(connection)
        except KeyboardInterrupt:
            print("Stopping Server...")

    def handle_connection(self, connection):
        try:
            req = self._recv_req(connection)
            print("Request: {}".format(req))
            # Method Validator
            if req["method"].upper() == "GET":
                try:
                    self._send_res(connection, self.get(req["query"]), 200)
                except IOError as e:
                    self._send_res(connection, "GET Error: {}".format(e), 400)
            elif req["method"].upper() == "PUT":
                print("reached")
                try:
                    self._send_res(connection, self.put(req["key"], req["value"]), 200)
                except IOError as e:
                    self._send_res(connection, "PUT Error: {}".format(e), 400)
            else:
                raise IOError('Request type must be GET/PUT')
        except Exception as e:
            print("exception")
            self._send_res(connection, "Bad Request: {}".format(e), 400)
        finally:
            connection.close()

    def get(self, key):
        if key in self.keyvaluedict:
            return self.keyvaluedict[key]
        else:
            raise IOError("Key doesn't exists")

    def put(self, key, value):
        print("I'm here {}".format(self.keyvaluedict))
        self.keyvaluedict[key] = value
        return self.keyvaluedict

def main():
    KeyValueServer().start()


if __name__ == '__main__':
    main()
