#!/usr/bin/env python

from multiprocessing import Process, Queue

def f(name, queue):
    print ('Hello', name)
    q.put([10, 'World', None])


if (__name__ == "__main__"):
    q = Queue()
    p = Process(target=f, args=('bob', q))  # args must be a tuple
    p.start()
    ret = q.get()
    print (ret)
    p.join()
