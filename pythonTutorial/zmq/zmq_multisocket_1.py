# Please read zmq_objects.txt and zmq_patterns.txt first
# What if we want to create a client which reads from multiple sockets at the same time

# Lets try to create a worker client and also a subscriber to weather updates.
# So look up zmq_PUB_server2.py
import zmq.green as zmq
import sys
import time
import signal


def signal_handler(signal_no, stack_frame):
    print('\nreceived signal %s' % signal_no)
    print('Exiting.. stack frame %s' % stack_frame)
    sys.exit(-1)


context = zmq.Context()
worker = context.socket(zmq.PULL)  # see zmq_PUSH_ventilator.py
worker.connect('tcp://localhost:6666')  # see zmq_PUSH_ventilator.py

subscriber = context.socket(zmq.SUB)
subscriber.connect('tcp://localhost:5557')  # see zmq_PUB_server_2.py
subscriber.setsockopt(zmq.SUBSCRIBE, '11')


# install your signal handler
signal.signal(signal.SIGINT, signal_handler)

# loop continuously
while True:
    while True:
        try:
            message = worker.recv(zmq.DONTWAIT)
            print('received worker task %s' % message)
        except zmq.Again:
            break

    while True:
        try:
            message = subscriber.recv(zmq.DONTWAIT)
            print('received weather update %s' % message)
        except zmq.Again:
            break

    time.sleep(0.001)  # sleep for a milli second before looking for an update again.

# This works but there are problems in this approach
# 1) You give more priority to worker tasks than weather updates
# 2) Too much while True looping
# 3) Sleeping in the end for 1 millisec
# 4) you have better option available called zmq_poll. Let's use it next