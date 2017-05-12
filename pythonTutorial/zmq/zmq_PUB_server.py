import zmq.green as zmq
import time

context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind('tcp://*:5556')

# public string Hello World and a string Cruel World every 1 second
while True:
    socket.send('Hello World')
    time.sleep(1)
    socket.send('Cruel World')
    time.sleep(1)
