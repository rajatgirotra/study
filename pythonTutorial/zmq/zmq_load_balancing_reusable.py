# Please read zmq_router_dealer_workers.py first
# Here we will build a simple load balancer which will process pre-determined requests and then exit
# Later we will see how to create a long running load balancer.

import zmq as zmq
import time
import random
import sys
import zhelpers
import multiprocessing


CLIENT_COUNT = 10
WORKER_COUNT = 3

FRONTEND = 'ipc://frontend.ipc'
BACKEND = 'ipc://backend.ipc'

# Note that since we are using multiprocess here, we can't really use inproc:// xport.
def worker_task(identity):
    # create REQ socket and connect to backend
    # For multiprocessing, each process should have its own independent context.
    # so can't use context = zmq.Context.instance() here.
    context = zmq.Context()
    worker = context.socket(zmq.REQ)
    ident = 'Worker_%s' % str(identity)
    worker.setsockopt_string(zmq.IDENTITY, ident)
    worker.connect(BACKEND)
    # print('%s connected' % ident)
    # Tell backend you are ready
    worker.send(b'READY')
    while True:
        # receive work
        client, empty, task = worker.recv_multipart()
        print('%s: %s' % (ident, task))
        # send result back
        worker.send_multipart([client, b'', b'OK!!'])


def client_task(identity):
    # create REQ socket and connect to backend
    context = zmq.Context()
    client = context.socket(zmq.REQ)
    ident = 'Client_%s' % str(identity)
    client.setsockopt_string(zmq.IDENTITY, ident)
    client.connect(FRONTEND)
    # print('%s connected' % ident)

    # send a request and await reply
    client.send(b'Hello')
    msg = client.recv()
    print('%s: %s' % (ident, msg))


def main():
    context = zmq.Context.instance()
    # create frontend and backend sockets and bind them
    frontend = context.socket(zmq.ROUTER)
    frontend.bind(FRONTEND)

    backend = context.socket(zmq.ROUTER)
    backend.bind(BACKEND)

    def start_task(task, *args):
        process = multiprocessing.Process(target=task, args=args)
        process.daemon = True
        process.start()

    # start workers first, then clients.
    for _ in range(WORKER_COUNT):
        start_task(worker_task, _)
    for _ in range(CLIENT_COUNT):
        start_task(client_task, _)

    # the main load balancer loop
    workers = []
    tasks_to_execute = CLIENT_COUNT
    poller = zmq.Poller()
    poller.register(backend, zmq.POLLIN)
    time.sleep(5)
    while True:
        sockets = dict(poller.poll())

        # Is reply from backend
        if backend in sockets:
            # this could be an initial ready message or a response after running a client task
            reply = backend.recv_multipart()
            worker, empty, client = reply[:3]
            # if workers queue was empty, start polling for new client requests
            if not workers:
                poller.register(frontend, zmq.POLLIN)
            # Add this worker to the Queue in both cases
            workers.append(worker)
            if client != b'READY' and len(reply) > 3:  # a task just finished
                # send response back to frontend
                empty, response = reply[3:]
                frontend.send_multipart([client, b'', response])
                tasks_to_execute -= 1
                if tasks_to_execute == 0:
                    break

        # is reply from frontend
        if frontend in sockets:
            # A new request from a client
            client, empty, task = frontend.recv_multipart()
            # worker will always be available
            worker = workers.pop(0)
            backend.send_multipart([worker, b'', client, b'', task])
            # if workers exhausted, stop polling for new tasks
            if not workers:
                poller.unregister(frontend)

    # cleanup
    frontend.close()
    backend.close()
    context.term()


if __name__ == "__main__":
    main()
