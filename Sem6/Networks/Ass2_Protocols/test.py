from threading import Thread, RLock
# import threading
class PrintP:

    def __init__(self):
        self.x =1
        self.lock = RLock()

    def pri(self, name):
        i=10
        while i:
            self.lock.acquire()
            print(self.x, name)
            self.x += 1
            self.lock.release()
            i-=1

m = PrintP()
Thread(target=m.pri, args=("1")).start()
Thread(target=m.pri, args=("2")).start()
