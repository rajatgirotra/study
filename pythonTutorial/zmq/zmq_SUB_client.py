import zmq.green as zmq
import time

context = zmq.Context()
socket = context.socket(zmq.SUB)  # a subscribe socket

# one SUB socket can connect to multiple publishers in which case the messages will be interleaved
# from all the publishers
socket.connect('tcp://localhost:5556')
socket.connect('tcp://localhost:5557')

# Simply connecting to the PUB socket isnt enough. We must SUBSCRIBE to something before publisher
# actually sends anything. For that we set a socket option on the socket instance.
# Remember that socket option must always be unicode not ascii string. You have already read
# about Python 2 and Python 3 ascii and unicode string
# filter on pincode : 110027
socket.setsockopt(zmq.SUBSCRIBE, '11')  # this means that messages starting with 11 will be delivered
# filter on string beginning with Hello
socket.setsockopt(zmq.SUBSCRIBE, 'Hello')  # this means that messages starting with 1100 will be delivered

if __name__ == '__main__':
    for index in range(20):
        message = socket.recv()
        print('Received %s' % message)


# Important Points
# 1. A SUB socket can talk to multiple publishers as you saw above
# 2. If two or more Subscribers are connected to the same publisher and one of the subscribers is slow,
# then the messages will be queued at the publisher. We'll see how HWM (High Water Mark) can help in this case.
# 3. The MOST IMPORTANT POINT: Even if we start subscriber first, and publisher latest, we will still loose some
# initial messages published by publisher. This is because ZMQ uses async I/O; so by the time the client and server
# handshake is complete, publisher will keep on sending messages which the client will miss. We'll see later how to fix this.


