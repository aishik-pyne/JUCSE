#!/usr/bin/python3
import socket
import json
import re
def _recv_req(connection):
    data = ""
    while True:
        buffer = connection.recv(16)
        if buffer:
            data += buffer.decode('utf-8')
        else:
            break
    return json.loads(data)

def hit_server(message, host='127.0.0.1', port=8000):
    sock = socket.socket()
    sock.connect((host, port))

    try:
        message = json.dumps(message).encode('utf-8')
        sock.sendall(message)
        
        print(_recv_req(sock))
        
    finally:
        sock.close()

def main():
    try:
        while True:
            ip = str(input(">"))
            tokens = re.split(' ', ip)
            if tokens[0].upper() == 'GET':
                hit_server({
                    "method": 'GET', 
                    "query": tokens[1]
                })
            elif tokens[0].upper() == 'PUT':
                hit_server({
                    "method": 'PUT', 
                    "key": tokens[1],
                    "value": tokens[2]
                })
                
    except KeyboardInterrupt:
        print("Bye")

if __name__ == '__main__':
    main()
