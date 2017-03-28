#!/usr/bin/env python

# coding: utf-8

# In[ ]:

import gevent
from gevent.greenlet import Greenlet
import socket


# In[ ]:

# gevent is a simple library proving an event loop at its core. Its very similar to asyncio in python 3 so if you have
# python 3, prefer using that. Lets' now se how to use it.

# gevent depends on a gevent library, greenlet is a simple library for wrapping functions and arguments togther.
# Lets see them in action.


# In[ ]:

# Creating a simple function and wrapping it in greenlet
def myfunction(arg1, arg2, **kwargs):
    print (arg1, arg2, kwargs)
    return 100


# In[ ]:

g = Greenlet(myfunction, 'One', 'Two', now='Buckle my shoe')  # create a Greenlet instance using c'tor
g.start()  # and then call start(), which immediately calls it, returns None always
g.join()
print('Finished')
print('Greenlet.value', g.value)  # Stores the function return value


# In[ ]:

# the other way is to use the spawn() method, which creates an instance and calls start() too.
# So it is a shorthand and widely used
jobs = [gevent.spawn(myfunction, '1', '2', now='Buckle my shoe') for i in range(0,5)]
gevent.joinall(jobs, timeout=3)  # the first parameter is reduced to a subset of jobs that finished under 3 seconds
[job.value for job in jobs]

