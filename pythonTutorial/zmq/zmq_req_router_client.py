import zmq.green as zmq
import sys
import signal
import string
import random


def signal_handler(signal_no, stack_frame):
    print('\nreceived signal %s' % signal_no)
    print('exiting.. stack frame %s' % stack_frame)
    sys.exit(-1)


client_name = ''.join([random.choice(string.ascii_letters + string.digits) for _ in xrange(7)])

context = zmq.Context()

# Create a REQ socket and connect to the ROUTER socket
socket = context.socket(zmq.REQ)
socket.connect('tcp://localhost:5559')

signal.signal(signal.SIGINT, signal_handler)

# Do ten requests
for _ in range(1, 11):
    socket.send('Hello from client %s' % client_name)
    message = socket.recv()
    print('client %s received response %s [%s]' % (client_name, _, message))

