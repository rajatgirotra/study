#!/usr/bin/env python

# Weather update subscriber

import zmq
import sys

if (__name__ == "__main__"):
    # Context
    context = zmq.Context()

    # Socket
    socket = context.socket(zmq.SUB)  # SUBscriber

    # Connect
    print ('Connecting to weather update server')
    socket.connect('tcp://localhost:5555')

    # Set Socket Options
    # ZMQ provides various options you can apply on a socket. Many of these options will have an associated value
    # Read here about these (not very difficult: http://api.zeromq.org/4-0:zmq-setsockopt)
    # be default, a SUB socket will filter out all incoming messages, so you must install a filter initially
    # to filter some message to be delivered. this filter can be applied using socket options.
    # We use the zmq.SUBSCRIBE socket option. It takes as value a prefix. If the incoming message has this prefix,
    # the message will be delivered. If the option value is empty, all messages will be delivered.
    # in python 2, this option value must be specified as a Unicode string, in python 3 it is a string
    zip_filter = sys.argv[1] if (len(sys.argv) > 1) else "11001"

    if (isinstance(zip_filter, bytes)):
        zip_filter = zip_filter.decode('utf-8')

    print (type(zip_filter))
    socket.setsockopt_string(zmq.SUBSCRIBE, zip_filter)
    # socket.setsockopt_string(zmq.SUBSCRIBE, ''.decode('utf-8'))  # To allow all messages

    # Process five updates
    total_temp = 0
    for update_nbr in range(5):
        message = socket.recv_string()
        print('Received update %s' % message)
        zip, temp, humid = message.split()
        total_temp += int(temp)

    print('Average temp for zip %s is %d F'
          % (zip_filter, total_temp/update_nbr))


# A very important note. It is possible that even though you start your subscriber first and then publisher,
# you may miss some messages from publisher, because some time (in millisec) is always taken up by the TCP layer
# for handshaking, and ZMQ socket might send something to subscriber which it may not receive.
# A very bad way to get paste it is to put sleep in publisher after binding and let subscribers connect. But very
# bad way ofcourse, Later we will see how to fix this.
