# Implement Data link layer protocols

- **Stop and Wait,**
- **Go Back N SlidingWindow**

---
**author:** Aishik Pyne  
**class:** BCSE3  
**Roll:** 12

## Stop and Wait

### Sender

The sender opens a socket and binds to localhost and predefined port.  
Input is taken from the user and using the CRC module in Ass1 it makes frames with a Checksum  

Iterate over the frames, and for each frame, **send** the frame using the method

```python
def _send_one_frame(self, frame, conn, corrupt_simulation=False):
      # Put in corruptions
      if randrange(0,10) <=2 and corrupt_simulation:
          frame = self.crc._corrupt_frame(frame)
      conn.sendall(str(frame).zfill(8).encode('utf-8'))
      # conn.flush()
      print('{} sent'.format(str(frame).zfill(8)))
```

Then it wait's for an **ack**

```python
def _receive_ack(self, conn):
      print('waiting for ack')
      ack = int(conn.recv(1))
      print('Received ack {}'.format(True if ack == 1 else False))
      if ack == 1:
          return True
      else:
          return False
```

If the ack is False, the frame is sent again

**Corruption simulation**

After the the frames are made, a random bit is flipped

### Receiver

The receiver waits for data.  
When a frame arives, it decodes and checks the Checksum.

```python
def _receive_one_frame(self):
      frame = self.socket.recv(8).decode('utf_8')
      print('Frame {} received'.format(frame))
      if frame:
          return int(frame)
      return None
```
If the frame is not corrupt it send a **True ack**, else a **False ack**

```python
def _send_ack(self, ack):
      if ack:
          self.socket.send('1'.encode('utf-8'))
      else:
          self.socket.send('0'.encode('utf-8'))
      print('Ack sent {}'.format(ack))
```

If the frame was valid it added is to the list of received frames.
Fianlly all the frames are assembled and the received text is dumped into a file.

---

## Go Back N

###  Sender

It maintains a window size, with a low and high pointer.
After a sending all frames in that window it waits for ack for TTL time.
If TTL expires it resends the frames

```python
while 1:
  x = open(tempfile, 'rb')
  fcntl.flock(x, fcntl.LOCK_EX )
  status = pickle.load(x)
  fcntl.flock(x, fcntl.LOCK_UN)
  # print(status)
  if status['transfer_complete']:
    print( "File transfer Complete ..")
    print( "Total time in seconds : " + str(time.time() - start_time))
    break

  print('Trying to send {}'.format(seq_no_to_send))
  message_to_send = pack_data(seq_no_to_send, frames[seq_no_to_send])
  client_socket.sendto(message_to_send,(server_host,port))
  # set_timeout(send_seq_no,tempfile)
  seq_no_to_send += 1
  if seq_no_to_send > status['window_high']:
    seq_no_to_send = status['window_low']
```


In another **thread** it receives the ack.
If ack is found for a seq no, the window slides forwards.
```python
def rcv_thread(soc):
	global window_size
	global total_frames
	global tempfile
	new_proc = os.fork()
	if new_proc == 0:
		print("Receive Thread " + str(os.getpid()) + " created..")
		while 1:
			while os.stat(tempfile).st_size == 0:
				continue

			status = pickle.load(open(tempfile, 'rb'))
			print(status)
			message, server_addr = soc.recvfrom(max_buff)
			message = pickle.loads(message)
			seq_no, ack = message['seq_num'], message['ack']
			print('\033[93mAck Rec {} value {}\033[0m'.format(seq_no, ack))
			if seq_no == total_frames-1:
				status['transfer_complete'] = True
				break
			if ack:
				status['window_low'] = seq_no+1
				status['window_high'] = status['window_low'] + window_size
				x = open(tempfile, 'wb')
				fcntl.flock(x, fcntl.LOCK_EX )
				pickle.dump(status, open(tempfile, 'wb') )
				fcntl.flock(x, fcntl.LOCK_UN)
```

### Receiver

Waits for frames and when found sends an ack if **valid** to the sender with the seq no received

```python
while 1:
  msg, client_address = s.recvfrom(65535)
  data = pickle.loads(msg)
  got_seq_no, frame = data['seq_num'], data['frame']
  print('Packet Recv seq_no {} '.format(got_seq_no))
  if random() < probability: # Random packet drop simulation
    decoded = crc.decode([frame], verbose=True)
    if decoded is not None: # Checksum is correct
      if got_seq_no == exp_seq_no: # Send ack
        to_send = rdt_send(got_seq_no)
        if to_send:
          s.sendto(to_send, client_address)
          f_write(decoded,output_file)
          exp_seq_no = exp_seq_no + 1
      elif got_seq_no > exp_seq_no: # Future packet received, hence dropped
        print ("Packet loss, sequence number = " + str(got_seq_no))
      elif got_seq_no < exp_seq_no: # Repeat sent
        to_send = rdt_send(exp_seq_no)
        if to_send:
        # print ("Retransmitted ACK - " + str(got_seq_no))
          s.sendto(to_send, client_address)
    else:
      print ("Checksum invalid. Packet dropped.")
  else: # Random packet drop simulation
    print ("Packet loss, sequence number = " + str(got_seq_no))
```
