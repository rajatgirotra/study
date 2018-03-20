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

zmq.proxy(frontend, backend)

# We'll never get here but close sockets and terminate context anyway
frontend.close()
backend.close()
context.term()