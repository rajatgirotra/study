import zmq.green as zmq
import sys
import time
import random

context = zmq.Context()

# PULL socket to accept tasks
worker = context.socket(zmq.PULL)
worker.connect('tcp://localhost:6666')

# PUSH socket to tell sink the task is done
sink = context.socket(zmq.PUSH)
sink.connect('tcp://localhost:6667')

# SUB socket to find when workers need to stop.
controller = context.socket(zmq.SUB)
controller.connect('tcp://localhost:6668')
controller.setsockopt(zmq.SUBSCRIBE, b'')  # subscribe to everything

poller = zmq.Poller()
poller.register(worker, zmq.POLLIN)
poller.register(controller, zmq.POLLIN)
while True:
    socks = dict(poller.poll())
    if socks.get(worker) == zmq.POLLIN:  # do work
        message = float(worker.recv())
        sys.stdout.write('.')
        sys.stdout.flush()
        time.sleep(message * 0.001)  # sleep in milliseconds
        # task done, signal sink
        sink.send(b'')
    if socks.get(controller) == zmq.POLLIN:
        message = controller.recv()
        print('\nWorker stopping')
        break

# finished
worker.close()
controller.close()
sink.close()
context.term()
