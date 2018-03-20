import zmq.green as zmq
import sys
import signal


def signal_handler(signal_no, stack_frame):
    print('\nreceived signal %s' % signal_no)
    print('exiting.. stack frame %s' % stack_frame)
    sys.exit(-1)


context = zmq.Context()

# Create a REQ socket and connect to the ROUTER socket
frontend = context.socket(zmq.ROUTER)
frontend.bind('tcp://*:5559')

backend = context.socket(zmq.DEALER)
backend.bind('tcp://*:5560')

signal.signal(signal.SIGINT, signal_handler)

poller = zmq.Poller()
poller.register(frontend, zmq.POLLIN)
poller.register(backend, zmq.POLLIN)

while True:
    socks = dict(poller.poll())
    if socks.get(frontend) == zmq.POLLIN:
        message = frontend.recv_multipart()
        backend.send_multipart(message)
    if socks.get(backend) == zmq.POLLIN:
        message = backend.recv_multipart()
        frontend.send_multipart(message)
    # print ('socks %s' % socks)

# this message broker code above is so common that ZMQ has a proxy method which creates the poller
# does the polling and sends and receives messages automatically. Lets use it.
