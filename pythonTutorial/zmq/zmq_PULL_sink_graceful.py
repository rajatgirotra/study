import zmq.green as zmq
import sys
import time

context = zmq.Context()

# PULL socket (from workers and ventilator) for workers ready and task completion
workers = context.socket(zmq.PULL)
workers.bind('tcp://*:6667')

# PUB socket to signal workers to stop
controller = context.socket(zmq.PUB)
controller.bind('tcp://*:6668')

# Wait for signal from ventilator first
workers.recv()

# Now be ready to accumulate task results
start_time = time.time()
for i in range(1, 101):
    workers.recv()
    if i % 10 == 0:
        sys.stdout.write(':')
    else:
        sys.stdout.write('.')

end_time = time.time()
# signal workers to stop
controller.send(b'')

print('\nTotal time taken by workers to process 100 tasks is %s seconds' % str(end_time-start_time))

# Next we'll get to Multithreading using ZMQ.
# To make utterly perfect MT programs (and I mean that literally),
# we don't need mutexes, locks, or any other form of inter-thread communication
# except messages sent across ZeroMQ sockets.
# If there's one lesson learned from 30+ years of concurrent programming, it is:
# JUST DON'T SHARE STATE.

# Next we will create a multithreaded version of a simple Hello World program. Where there are
# multiple external clients connecting to server via TCP, and the server has spawned five threads
# to service client requests. We could also have done this using a proxy broker (like a ROUTER and
# DEALER) and have external backend processes instead of threads in one process, but this approach
# is better because
# 1) With separate backend processes you need to write an external broker process.
# 2) using threads, you prevent a network hop. All threads will use the inproc:// zmq socket type,
# so it is much faster; as you cut a network hop.
# Let's see it in action.
# Read zmq_hello_world_mt.py
