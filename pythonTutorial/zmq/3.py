#!/usr/bin/env python

# Lets do PUBlish, SUBscribe with ZMQ, pretty easy. This is the server

import zmq
# import time
import signal
import sys

def signal_handler(signal_no, stack_frame):
    print('Signal received %i' % signal_no)
    print('Stack frame %s' % stack_frame)
    sys.exit(-1)

from random import randrange

if (__name__ == "__main__"):
    # Context
    context = zmq.Context()

    # Socket
    socket = context.socket(zmq.PUB)  # Publisher

    # Bind socket
    socket.bind("tcp://*:5555")

    # Create a signal handler
    signal.signal(signal.SIGINT, signal_handler)

    # Push random weather updates
    while True:
        zipcode = randrange(1, 100000)
        temp = randrange(-50, 50)
        humidity = randrange(10, 70)

        # Note we are sending a string now.
        socket.send_string('%i %i %i' % (zipcode, temp, humidity))

# Note that if you start publisher, it will simply keep dropping
# all messages as there are no subscribers.
# Also, PUB SUB is TCP based, so TCP flow control will be used.
# This means that for a slow subscriber, messages will be queued on the publisher
# We will see later how to protect publishers using HWM (High-water-mark) later.
