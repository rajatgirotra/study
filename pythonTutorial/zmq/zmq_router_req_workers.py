# Please read zmq_load_balancing.txt first

import zmq.green as zmq
import sys
import signal
import threading
import zhelpers
import time
import random


def worker_thread(index):
    context = zmq.Context.instance()
    # Create a REQ socket
    worker = context.socket(zmq.REQ)
    identity = 'Worker_%s' % index
    worker.setsockopt_string(zmq.IDENTITY, identity)
    worker.connect('inproc://example')

    # Process tasks continuously
    total_tasks = 0
    try:
        while True:
            # Send a ready message
            worker.send(b'READY')

            # receive task
            msg = worker.recv()
            if msg == b'END':
                break
            total_tasks += 1
            # do some random work
            time.sleep(0.1 * random.random())
    except (KeyboardInterrupt, zmq.ContextTerminated):
        print('%s interrupted..' % identity)
    finally:
        print('%s processed %s tasks' % (identity, total_tasks))


WORKERS_COUNT = 10
context = zmq.Context.instance()
# Create a router socket (use inproc:// xport)
router = context.socket(zmq.ROUTER)
router.bind('inproc://example')

# Create 10 worker threads
for _ in range(WORKERS_COUNT):
    threading.Thread(target=worker_thread, args=(_,)).start()


# Submit WORKERS_COUNT * 10 tasks
for _ in range(WORKERS_COUNT*10):
    address, empty, msg = router.recv_multipart()
    router.send_multipart([address, b'', b'This is the workload'])

# Finally signal workers to finish
for _ in range(WORKERS_COUNT):
    address, empty, msg = router.recv_multipart()
    router.send_multipart([address, b'', b'END'])

# Please read zmq_router_dealer_workers.py next
