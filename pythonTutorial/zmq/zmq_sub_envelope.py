import zmq.green as zmq
import sys
import time


def main():
    context = zmq.Context.instance()
    subscriber = context.socket(zmq.SUB)
    subscriber.connect('tcp://localhost:6767')
    subscriber.setsockopt(zmq.SUBSCRIBE, b'B')

    try:
        while True:
            [key, data] = subscriber.recv_multipart()
            print('Message key: [%s], data: %s' % (key, data))
    except KeyboardInterrupt:
        pass
    finally:
        subscriber.close()
        context.term()


if __name__ == "__main__":
    main()
