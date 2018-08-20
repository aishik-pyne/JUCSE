import socket, json

sock = socket.socket()
sock.connect(('localhost', 5000))
message = json.dumps("asfddadf").encode('utf-8')
sock.sendall(message)