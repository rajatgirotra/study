import zmq.green as zmq
import time
# Will create a server REP socket

context = zmq.Context()
# Create a REP socket.
socket = context.socket(zmq.REQ)
socket.connect('tcp://localhost:5555')

for index in range(10):
    socket.send(b'Hello ')
    message = socket.recv()
    print('Client received %s' % message)
    time.sleep(1)  # wait half a minute
