
import socket, json, pickle
class HttpServer():
    """
    The sever communicates using JSON objects.
    Req format:
        {
            "method": "GET",
            "headers: {
                "username": "abcd",
                "return self.store[targetUser]word": "1234"
            },
            "body": {
                "city": "kolkata"
            }
        }
    """
    def __init__(self, host, port, authFilePath='httpass.json'):
        self.host = host
        self.port = port
        if authFilePath:
            self.auth = True
            self.users = json.load(open(authFilePath, 'r'))
        else: 
            self.auth = False

    def _authenticate(self, authHeader):
        for user in self.users:
            if user["username"] == authHeader["username"] and \
                user["password"]==authHeader["password"]:
                return user
        raise ValueError("Username password incorrect")

    def receive(self, connection, client_address):
        buff = connection.recv(8192)
        req = pickle.loads(buff)
        print(type(req))

        if self.auth:
            # Parse the auth token
            try:
                authHeader = { key: req['headers'][key] for key in ["username", "password"] }
            except (KeyError, TypeError) as e:
                print("Bad Request during auth parse {}".format(e))
                self.send(connection, {
                    "response": "Bad Request during auth parse - Username Password not provided", 
                },
                400)
                raise
            
            # Authenticate the user
            try:
                user = self._authenticate(authHeader)
                print("User is authenticated...")
            except ValueError as e:
                print("Authentication Error {}".format(e))
                self.send(connection, {
                    "response": "Authentication Error {}".format(e), 
                },
                401)
                raise

        # Validate the request
        try:
            method = req["method"]
            body = req["body"]
            if not self.auth:
                user = None
        except KeyError as e:
            print("Validation Error {}".format(e))
            self.send(connection, {
                "response": "Validation Error {}".format(e), 
            },
            400)
        return (method, body, user)
            

    def send(self, connection, response, status):
        connection.sendall(pickle.dumps((response, status)))

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
                try:
                    request = self.receive(connection, client_address)
                    print("Request parsed")
                    response, status = self.handle_reqest(request)
                    print("Request Handled")
                    self.send(connection, response, status)
                    print("Response Sent")
                except Exception as e:
                    print(e)
        except KeyboardInterrupt:
            print("Stopping Server...")

    def handle_reqest(self, request):
        raise NotImplementedError

import sys
# Server = HttpServer('localhost', int(sys.argv[1]), authFilePath='httpass.json')
# Server.start()


class KeyValueServer(HttpServer):
    def __init__(self):
        HttpServer.__init__(self, 'localhost', int(sys.argv[1]))
        self.store = {}
        self.start()
    
    def put(self, key, value, user):
        if user["username"] not in self.store:
            self.store[user["username"]] = {}
        self.store[user["username"]][key] = value

    def get(self, key, user, targetUserName = None):
        targetUserName = targetUserName if targetUserName else user["username"]
        print(targetUserName)
        if user["role"] == 'guest' and user["username"] != targetUserName:
            raise ValueError('Unautheticated use')
        return self.store[targetUserName][key]

    def handle_reqest(self, request):
        method, body, user = request
        # print(user)
        try:
            try:
                if method == "GET":
                    key = body["key"]
                    user = user
                    try:
                        value = self.get(key, user)
                        return (value, 200)
                    except Exception as e:
                        print(e)
                        return "Error in GET", 400
                elif method == "PUT":
                    key = body["key"]
                    value = body["value"]
                    user = user
                    try:
                        self.put(key, value, user)
                        return "Success", 200
                    except Exception as e:
                        print(e)
                        return "Error in PUT", 400
                    
            except KeyError as e:
                return ("Invalid Method", 400)
        except Exception as e:
            print(e)
            return ("Something went wrong", 500)
        finally:
            print(self.store)

KeyValueServer()