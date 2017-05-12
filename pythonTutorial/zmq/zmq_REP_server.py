# ZMQ is extremely simple. It implements communication protocols like
# REQUEST REPLY
# PUB SUB
# PUSH PULL (Divide and Conquer) etc.

# Lets begin with Request and Reply. Strictly is Request, Reply. If either client or server
# sends two messages, the API will return with an error. Also the REQ socket should initiate
# the first message.

import zmq.green as zmq

# Will create a server REP socket.
context = zmq.Context() # we'll explore arguments to this function later.
# Create a REP socket.
socket = context.socket(zmq.REP)
socket.bind('tcp://*:5555')  # * means all interfaces, eth0, wireless etc

while True:
    message = socket.recv()
    print ('Server received %s' % message)
    socket.send('World')
