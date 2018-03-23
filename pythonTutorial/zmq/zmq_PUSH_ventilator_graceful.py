# Here we will use the same PUSH, PULL model to fan out work to multiple workers processes.
# However, we will see how to gracefully shutdown the workers. Here the SINK process will create
# a new PUB socket and all workers will create a SUB socket. When they receive a signal from SINK
# all workers will stop. We also handle Ctrl+C interrupt by catching the KeyboardInterrupt exception
# instead of having a signal handler.

import zmq.green as zmq
import sys
import time
import random

context = zmq.Context()
# PUSH (fan out work)
workers = context.socket(zmq.PUSH)
workers.bind('tcp://*:6666')

# Open a push socket to sink too, to inform it to start collecting data.
sink = context.socket(zmq.PUSH)
sink.connect('tcp://localhost:6667')
input('--->> Enter when all worker processes are ready!!')
sink.send(b'0')
print('sending 100 tasks to workers')

random.seed()
total_time = 0

# Push 100 tasks to workers.
for i in range(100):
    # get a random int
    wait_time = random.randint(1, 100)
    total_time += wait_time
    workers.send_string('%s' % str(wait_time))

print('\nTotal wait time for all tasks to finish is %s seconds' % str(float(total_time)/1000))

# wait for ZMQ thread to actually send all tasks.
time.sleep(5)
