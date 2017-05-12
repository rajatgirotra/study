import zmq.green as zmq
import sys
import time

context = zmq.Context()
sink = context.socket(zmq.PULL)
sink.bind('tcp://*:6667')

# first message tells that workers are ready
sink.recv()

start_time = time.time()
for index in range(100):
    sink.recv()
    if index % 10 == 0:
        sys.stdout.write(':')
    else:
        sys.stdout.write('.')
    sys.stdout.flush()


end_time = time.time()
print('Total time taken to process 100 tasks is %s seconds' % (end_time-start_time))
