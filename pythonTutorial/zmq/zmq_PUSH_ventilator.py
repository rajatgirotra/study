# Here we will show the PUSH/PULL model for parallel pipeline. We can use this model to do parallel
# processing. What we'll do
# 1. Create a PUSH socket to submit tasks.
# 2. Create multiple parallel processes all of which will open a PULL socket to connect to PUSH socket
# in step 1. The difference between PUB/SUB and this is that a Publisher message will be received by all
# subscribers. But a PUSH message will be received by only one of the connecting PULL sockets.
# 3. Create a single PUSH socket or SINK which will receive results from all PULL sockets and aggregate
# them. Effectively, we are distributing tasks submitted by PUSH socket to multiple workers (PULL sockets)
# and finally assemble/aggregate results in the final PUSH (sink) socket.

# Also note that zmq doesn't strictly require that the server should call bind and client should call connect
# It can also be other way round. But the best rule to follow here is that processes like worker processes here
# can be many. So they must call connect. Because we can start many of them. And fixed processes like ventilator
# and sink here should call bind.
import time
import zmq.green as zmq
import random

context = zmq.Context()
sender = context.socket(zmq.PUSH)
sender.bind('tcp://*:6666')

# open a connection to the sink, PUSH connection as you'll be sending data
sink = context.socket(zmq.PUSH)
sink.connect('tcp://localhost:6667')
input('--->> Enter when all worker threads are ready')
print ('sending 100 tasks to workers')
# Send a signal to the sink to start collecting data
sink.send('0')
# How to close the socket in zmq??

random.seed()
total_time = 0

for index in range(100):
    # get random millisec
    wait_time = random.randint(1, 100)
    total_time += wait_time
    sender.send('%s' % wait_time)

print ('Total wait time expected for tasks to finish is %s seconds' % str(float(total_time)/1000))

# Important wait for ZMQ to deliver tasks
time.sleep(5)
