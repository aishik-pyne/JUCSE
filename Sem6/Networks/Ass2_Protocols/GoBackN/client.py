import socket
import sys
from collections import namedtuple
import pickle
import threading
import inspect
import time
import signal


DATA_TYPE = 0b101010101010101
DATA_SIZE = 64   #need to be modified

data_pkt = namedtuple('data_pkt', 'seq_num checksum data_type data')
ack_pkt = namedtuple('ack_pkt', 'seq_num zero_field data_type')
N = 0  # window size
MSS = 0 # maximum segment size
ACK = 0 # ACK received from server.
num_pkts_sent = 0
num_pkts_acked = 0
seq_num = 0
window_low = 0
window_high = int(N)-1
total_pkts = 0
RTT = 2
pkts = []
done_transmitting = 0
starttime = 0
stoptime= 0




ack_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP Foo
host = socket.gethostname()
ack_port_num = 62223
ack_socket.bind((host, ack_port_num))

lock = threading.RLock()

def carry_checksum_addition(num_1, num_2):
    c = num_1 + num_2
    return (c & 0xffff) + (c >> 16)

def calculate_checksum(message):
    checksum = 0
    for i in range(0, len(message), 2):
        my_message = str(message)
        w = ord(my_message[i]) + (ord(my_message[i+1]) << 8)
        checksum = carry_checksum_addition(checksum, w)
    return (not checksum) & 0xfff



def pack_data(message, seq_num):
    pkt = data_pkt(seq_num, calculate_checksum(message), DATA_TYPE, message)
    my_list = [pkt.seq_num, pkt.checksum, pkt.data_type, pkt.data]
    packed_pkt = pickle.dumps(my_list)
    return packed_pkt


def prepare_pkts(file_content, seq_num):
    pkts_to_send = []
    seq_num = 0
    for item in file_content:
        pkts_to_send.append(pack_data(item, seq_num))
        seq_num += 1
    return pkts_to_send


def socket_function(pkts):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    host = socket.gethostname()
    port = 7735
    s.sendto(pkts, (host, port))
    s.close()

def timer(s,f):
    global pkts
    global window_low
    global window_high
    global total_pkts
    global ACK

    resent_index = window_low  # resent from window_low to window_high
    if ACK == window_low:
        print ("Timeout sequence number ="+ str(ACK))
        lock.acquire()
        while resent_index <= window_high and resent_index < total_pkts:
            signal.alarm(0)
            signal.setitimer(signal.ITIMER_REAL, RTT)
            socket_function(pkts[resent_index])
            resent_index += 1
        lock.release()


def send_file(file_content, sock, hostname, port):
    global total_pkts
    total_pkts = len(file_content)
    #print(total_pkts)
    global pkts
    global seq_num
    global RTT
    pkts= prepare_pkts(file_content, seq_num)
    global num_pkts_sent
    current_max_window = min(int(N), int(total_pkts))
    signal.setitimer(signal.ITIMER_REAL, RTT)
    while num_pkts_sent < current_max_window :

        if ACK == 0:
            socket_function(pkts[num_pkts_sent])
            num_pkts_sent += 1
        else:
            break


def ack_listen_thread(sock, host, port):
    global window_high
    global window_low
    global num_pkts_sent
    global num_pkts_acked
    global total_pkts
    global ACK
    global done_transmitting
    global stoptime
    done_transmitting = 0
    while True:
        data = pickle.loads(ack_socket.recv(256))
        if data[2]=="1010101010101010":
            ACK = data[0]
            if ACK:
                lock.acquire()
                if ACK >= window_low and ACK <total_pkts:
                    signal.alarm(0)
                    signal.setitimer(signal.ITIMER_REAL, RTT)
                    temp_pckts_acked = ACK - window_low
                    old_window_high = window_high
                    window_high = min(window_high + ACK - window_low, total_pkts-1)
                    window_low = ACK
                    num_pkts_acked += temp_pckts_acked  # Acked # of packages. Foo

                    for i in range(int(window_high-old_window_high)):
                        socket_function(pkts[num_pkts_sent])
                        if num_pkts_sent < total_pkts-1:
                                num_pkts_sent += 1

                elif ACK == total_pkts:
                    print("Done!")
                    done_transmitting = 1
                    stoptime = time.time()
                    print("Running Time:",str(stoptime-starttime))
                    exit()

                lock.release()

def parse_command_line_arguments():
    host = socket.gethostname()
    port = sys.argv[1]
    file_name = sys.argv[2]
    # my_window_size = sys.argv[4]
    # my_mss = sys.argv[5]

    return host, int(port), file_name, int(4), int(1)


def main():
    global N
    global MSS
    global starttime
    starttime = time.time()
    host, port, my_test_file, N, MSS = parse_command_line_arguments()
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Create a socket object

    print("Host:", host)
    port = 7735  # Reserve a port for your service.

    global window_high
    window_high = int(N)-1
    signal.signal(signal.SIGALRM, timer)
    try:
        file_content = []
        with open(my_test_file, 'rb') as f:
            while True:
                chunk = f.read(int(MSS))  # Read the file MSS bytes each time Foo
                if chunk:
                    file_content.append(chunk)
                else:
                    break
    except:
        sys.exit("Failed to open file!")

    send_file(file_content, s, host, port)
    threading.Thread(target=ack_listen_thread, args=(s, host, port)).start()
    s.close()


if __name__ == "__main__":
    main()
