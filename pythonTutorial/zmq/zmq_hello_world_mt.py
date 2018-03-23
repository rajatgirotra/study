import zmq.green as zmq
import sys
import threading
import time


def worker_routine(worker_url, context=None):
    context = context or zmq.Context.instance()

    # These are going to be reply socket type
    service = context.socket(zmq.REP)
    service.connect(worker_url)

    # Get message, process and reply
    while True:
        message = service.recv()
        print('Received request: [%s]' % message)
        time.sleep(1)
        service.send(b' World')


def main():
    context = zmq.Context.instance()

    # create a tcp socket for external clients to connect
    # we need a router socket, you we can handle requests asynchronously from multiple clients
    clients = context.socket(zmq.ROUTER)
    clients.bind('tcp://*:5555')

    # create an inproc:// socket to pass client message to one of the five threads.
    # these will be dealer sockets, so they can asynchronously process request and reply.
    workers = context.socket(zmq.DEALER)
    worker_url = 'inproc://workers'
    workers.bind(worker_url)

    # Launch a pool of 5 background threads.
    for i in range(5):
        thread = threading.Thread(target=worker_routine, args=(worker_url, ))
        thread.start()

    try:
        zmq.proxy(clients, workers)
    except KeyboardInterrupt:
        pass
    finally:    # finished, cleanup
        clients.close()
        workers.close()
        context.term()


if __name__ == "__main__":
    main()

# Run this along with multiple client processes zmq_REQ_client.py
# Here the "work" is just a one-second pause. We could do anything in the workers,
# including talking to other nodes. This is what the MT server looks like in terms of ØMQ sockets
# and nodes. Note how the request-reply chain is REQ-ROUTER-queue-DEALER-REP.

# Next we'll see how to signal between the threads in ZMQ. The ONLY WAY of signalling between thread
# is by sending ZMQ messages on the sockets.

# We'll use PAIR sockets for that. Read zmq_PAIR_signalling.py next