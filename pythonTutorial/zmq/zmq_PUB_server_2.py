import zmq.green as zmq
from random import randrange
import time

context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind('tcp://*:5557')

# public zipcode, temperature and humidity
while True:
    zipcode = randrange(100000, 130000)
    temperature = randrange(-25, 50)
    humidity = randrange(10, 60)
    socket.send('%s %s %s' % (zipcode, temperature, humidity))
    time.sleep(1)
