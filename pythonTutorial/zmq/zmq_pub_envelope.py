# PUB SUB works by looking at the prefix in the incoming data to decide if it needs to send message
# to subscriber or not. So we need to be sure that the prefix is always correct and that it doesnt actually
# accidentally match data. For this a better way is to:
# 1) Always have multipart messages in PUB, SUB architecture
# 2) Break your message into a key and data. Both key and data are sent in separate ZMQ frames
# 3) Send key first which will be used to match the prefix.
# 4) ZMQ never matches across frame boundaries, so data will never be used to match prefix.
# Let's see it in action

import zmq.green as zmq
import sys
import time


def main():
    context = zmq.Context.instance()
    publisher = context.socket(zmq.PUB)
    publisher.bind('tcp://*:6767')

    try:
        while True:
            publisher.send_multipart([b'A', b'We would not like to see this message'])
            publisher.send_multipart([b'B', b'We would like to see this message'])
            time.sleep(1)
    except KeyboardInterrupt:
        pass
    finally:
        publisher.close()
        context.term()


if __name__ == "__main__":
    main()
