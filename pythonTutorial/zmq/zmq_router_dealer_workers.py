# Please read zmq_router_rep_workers.py first
# This is very similar to that one, except that we use DEALER sockets in place of REQ. Why?
# 1) DEALER sockets are asynchronous, so a worker can call recv() more than once without calling
# send().
# 2) The DEALER socket doesnt need to send an empty delimiter frame (the ready message in the last
# program).

import zmq.green as zmq
import threading
import time
import random


def worker_thread(index):
    ctx = zmq.Context.instance()
    # Create a REQ socket
    worker = ctx.socket(zmq.DEALER)
    identity = 'Worker_%s' % index
    worker.setsockopt_string(zmq.IDENTITY, identity)
    worker.connect('inproc://example')

    # Process tasks continuously
    total_tasks = 0
    try:
        while True:
            # receive task. A DEALER SOCKET IS OBLIVIOUS TO THE PRESENCE OF A REPLY ENVELOPE.
            # IT JUST FAIR HANDLES MULTIPART MESSAGES FROM VARIOUS CONNECTIONS INTO A SINGLE QUEUE
            # AND IT DISTRIBUTES MESSAGES FAIRLY SENT OUT TO MULTIPLE CONNECTIONS.
            # IN OUR CASE, THERE IS ONLY ONE INPUT (the ROUTER) and one OUTPUT (the ROUTER) connection
            # ALSO, WE DONT EXPECT TO RETRIEVE MULTIPART MESSAGES, SO WE JUST USE PLAIN recv() function.
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


# NOTE THE DIFFERENCE HERE FROM LAST ONE. In the last program, the worker threads did a send() call,
# but here the workers thread do not need it, so we need to wait a second or two to allow all
# workers to be setup.
time.sleep(2)

# Submit WORKERS_COUNT * 10 tasks
for _ in range(WORKERS_COUNT*10):
    # Here is the MAIN DIFFERENCE, MUST READ THIS.
    # A ROUTER SOCKET IS OBLIVIOUS TO THE PRESENCE OF A REPLY ENVELOPE. WHEN SENDING OUT A
    # MULTIPART MESSAGE, IT JUST USES THE FIRST FRAME AS AN IDENTITY OF THE PEER TO SEND THE
    # MESSAGE TO, AND SEND ALL REMAINING FRAMES TO THE PEER
    wkr = 'Worker_%s' % str(random.randint(0, 9))
    router.send_multipart([wkr.encode('ascii'), b'This is the workload'])

# Finally signal workers to finish
for _ in range(WORKERS_COUNT):
    wkr = 'Worker_%s' % str(_)
    router.send_multipart([wkr.encode('ascii'), b'END'])

# time.sleep(5)

# Next we can now move on to a full fledged load balancing message broker
# We'll have REQ clients, talking to a frontend ROUTER sockets. This frontend ROUTER will be a proxy
# for a backend ROUTER sockets. The backend will talk to multiple REQ workers.
# Please read zmq_load_balancing_reusable.py next
