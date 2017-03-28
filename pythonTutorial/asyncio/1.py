#!/usr/bin/env python
# coding: utf-8

# In[1]:

# Lets study about asyncio python library. Very trivial. Its just an event loop at its core. Like you have it in Qt
# framework too. So it is single-threaded and can dispatch events, callbacks and also provide TCP/UDP server and
# client capabilities, as you'll see.
import asyncio


# In[2]:

# Get the basic event loop
event_loop = asyncio.get_event_loop()


# In[3]:

print(type(event_loop))


# In[ ]:

# Some functions which you can run on event loops
print(event_loop.is_running())
event_loop.run_forever()  # Blocking call, will start the event loop in the current thread.
print('Hello World')

print(event_loop.is_running())
