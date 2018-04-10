import zmq.green as zmq
import zhelpers

context = zmq.Context()
sink = context.socket(zmq.ROUTER)
sink.bind('inproc://example')

# Create an anonymous connection to ROUTER socket and send a message
anonymous = context.socket(zmq.DEALER)  # remember DEALER is like an async REQ socket
anonymous.connect('inproc://example')
anonymous.send(b'ROUTER uses a random 5 byte identity')
zhelpers.dump(sink)

peer2 = context.socket(zmq.DEALER)
peer2.setsockopt(zmq.IDENTITY, b'PEER2')
peer2.connect('inproc://example')
peer2.send(b'ROUTER uses DEALER\'s identity')
zhelpers.dump(sink)

anonymous.close()
peer2.close()
context.term()

# Please read zmq_load_balancing.txt next