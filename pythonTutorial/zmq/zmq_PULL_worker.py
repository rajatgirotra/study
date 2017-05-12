import zmq.green as zmq
import time
import sys

context = zmq.Context()
socket = context.socket(zmq.PULL)
socket.connect('tcp://localhost:6666')

sink = context.socket(zmq.PUSH)
sink.connect('tcp://localhost:6667')

while True:
    message = socket.recv()
    message = float(message)
    # show a progress indicator
    sys.stdout.write('.')
    sys.stdout.flush()
    time.sleep(message * 0.001)  # wait for message milliseconds
    # Wait over signal to sink
    sink.send('')