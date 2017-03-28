#!/usr/bin/env python

# ZMQ client.

import zmq

if (__name__ == "__main__"):
    # create context
    context = zmq.Context()

    # create socket
    socket = context.socket(zmq.REQ)  # Request socket

    # client will now connect
    print ('Connecting to hello world server...')

    socket.connect('tcp://localhost:5555')

    # Write b'Hello' 10 times
    for i in range(10):
        print ('Sending request %s ...' % i)
        # send data on socket
        socket.send(b'Hello')

        # Wait for reply
        message = socket.recv()
        print ('Received reply %s [ %s ] ' % (i, message))


# the request/reply sockets are strictly request reply. One end sends a request
# and then must wait for a reply. If any ends tries to do multiple send() or recv()
# it will be an error. The end which open the socket using zmq.REQ must first send
# a message.

# There are many different socket types which you can use
# REQ, REP, PUB, SUB, PAIR, DEALER, ROUTER, PULL, PUSH, etc.
