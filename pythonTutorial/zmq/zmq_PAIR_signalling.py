# We'll create three threads where thread 1 will signal thread 2 and thread 2 will signal thread 3.
# signalling is done by sending ZMQ messages.

import zmq.green as zmq
import sys
import time
import threading


def thread1():
    # Create a PAIR socket
    context = zmq.Context.instance()
    socket2 = context.socket(zmq.PAIR)
    socket2.connect("inproc://thread2")
    socket2.send(b'')
    socket2.close()


def thread2():
    # Create a PAIR socket
    context = zmq.Context.instance()
    socket = context.socket(zmq.PAIR)
    socket.bind("inproc://thread2")

    socket3 = context.socket(zmq.PAIR)
    socket3.connect("inproc://thread3")

    # create thread1 now
    thread = threading.Thread(target=thread1)
    thread.start()

    # Wait for a signal from thread1
    try:
        socket.recv()
        # signal thread3 now
        socket3.send(b'')
    except KeyboardInterrupt:
        pass
    finally:
        socket.close()
        socket3.close()


def main():
    # Create a PAIR socket
    context = zmq.Context.instance()
    socket = context.socket(zmq.PAIR)
    socket.bind("inproc://thread3")

    # create thread2 now
    thread = threading.Thread(target=thread2)
    thread.start()

    # Wait for a signal from thread2
    try:
        socket.recv()
        print('Test successful')
    except KeyboardInterrupt:
        pass
    finally:
        socket.close()
        context.term()


if __name__ == "__main__":
    main()


# We could have used PUB, SUB socket, but PAIR sockets are exclusive, and with PUB,SUB you will need
# to subscribe

# We could use PUSH, PULL but PUSH will distribute the message to all receivers, which is not intended.

# we could use ROUTER, DEALER, but ROUTER wraps your messages in an envelope. So suddenly your zero
# sized signal messages will turn into multipart messages. Also DEALER distributes your messages just
# like PUSH; so not worth using here.

# Please read zmq_node_coordination.txt