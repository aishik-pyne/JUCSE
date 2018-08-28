import socket, json, pickle, sys

sock = socket.socket()
sock.connect(('localhost', int(sys.argv[1])))
message = {
    "method": "PUT",
    "headers": {
        "username": "aishik-pyne",
        "password": "123456"
    },
    "body": {
        "key": "school",
        "value": "sxc"
    }
}
# message = json.dumps(message).encode('utf-8')
pkldumps = pickle.dumps(message)
sock.sendall(pkldumps)
# print(message)
# sock.sendall(None)

buff = sock.recv(4096)
response, status  = pickle.loads(buff)
print(response)


