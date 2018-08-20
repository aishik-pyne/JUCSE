
import socket, json, ioce
class HttpServer():
    """
    The sever communicates using JSON objects.
    Req format:
        {
            "method": "GET",
            "headers: {
                "username": "abcd",
                "password": "1234"
            },
            "body": {
                "city": "kolkata"
            }
        }
    """
    def __init__(self, host, port, authFilePath=None):
        self.host = host
        self.port = port
        if authFilePath:
            self.auth = True
            self.users = json.load(open(authFilePath, 'r'))
        else: 
            self.auth = False

    def receive(self, connection, client_address):
        req = ""
        while True:
            buff = connection.recv(16)
            req += buff.decode('utf-8')
            if not buff:
                break
        req = json.loads(req)
        try:
            authHeader = { your_key: req['haeders'][your_key] for your_key in ["username", "password"] }
        except KeyError as e:
            print("Bad Request {}".format(e))
            self.send(connection, {
                "response": "Bad Request", 
            },
            400)

    def send(self, connection, response, status):
        resStr = (json.dumps(response)).encode('utf-8')
        print(type(resStr))

    def start(self):
        self.socket = socket.socket()
        self.socket.bind((self.host, self.port))
        self.socket.listen(1)
        print("Server started on host {} port {}".format(self.host, self.port))
        try:
            while True:
                connection, client_address = self.socket.accept()
                # connection.setblocking(1)
                # print('Got connection from {}', client_address)
                request = self.receive(connection, client_address)
                response, status = self.handle_reqest(*request)
                self.send(connection, response, status)
        except KeyboardInterrupt:
            print("Stopping Server...")

    def handle_reqest(self, method, endpoint, query, data):
        raise NotImplementedError


Server = HttpServer('localhost', 5000)
Server.start()