# Please read zmq_objects.txt and zmq_patterns.txt first
# lets use zmq_poll in this example which is much cleaner.
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

# create a poller object
poller = zmq.Poller()

# register the sockets which you are interested in getting data on.
poller.register(worker, zmq.POLLIN)  # POLLIN means you want to wait for data to be available
poller.register(subscriber, zmq.POLLIN)

while True:
    socks = dict(poller.poll())  # poller.poll() return a list of tuples of the
    # form (socket, event) where event is POLLIN or POLLOUT. We convert the tuple to dict here

    if worker in socks:
        message = worker.recv()
        print('received worker task %s' % message)
    if subscriber in socks:
        message = subscriber.recv()
        print('received weather update %s' % message)

# Please read zmq_dynamic_discovery.txt next