#!/usr/bin/env python

# ZMQ Server. Expects b"Hello" from client. replies with b"World

import time
import zmq
import signal
import sys


def signal_handler(signal_no, stack_frame):
    print ('Received signal %s' % signal_no)
    print ('Stack Frame\n %s' % str(stack_frame))
    sys.exit(-1)

if (__name__ == "__main__"):
    # The first thing to do is to create a zmq context
    context = zmq.Context()
    # Then you create a zmq socket
    socket = context.socket(zmq.REP)  # A reply socket.
    # Now bind the socket to a port
    socket.bind("tcp://*:5555")

    # install a signal handler which will be called when terminating server
    signal.signal(signal.SIGINT, signal_handler)

    # Wait for the client to send something and reply with b"Hello"
    while True:
        # wait
        message = socket.recv()
        print("Received request: %s" % message)

        # Do some work
        time.sleep(1)

        # Send response to client
        socket.send(b"World")
