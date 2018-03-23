import zmq.green as zmq
import sys
import signal
import string
import random


def signal_handler(signal_no, stack_frame):
    print('\nreceived signal %s' % signal_no)
    print('exiting.. stack frame %s' % stack_frame)
    sys.exit(-1)


context = zmq.Context()

server_name = ''.join([random.choice(string.ascii_letters + string.digits) for _ in range(7)])

# Create a REQ socket and connect to the ROUTER socket
socket = context.socket(zmq.REP)
socket.connect('tcp://localhost:5560')

signal.signal(signal.SIGINT, signal_handler)

# Handle requests
while True:
    message = socket.recv()
    print('server %s received request [%s]' % (server_name, message))
    socket.send(' World from server %s' % server_name)

