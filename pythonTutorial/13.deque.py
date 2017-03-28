#!/usr/bin/env python3
## Using lists as queues is not very effective as elements have to be moved up at every pop() operation.
## so better to use deque for that. Very easy same interface as list for append, for popping just use popleft() instead of pop()

from collections import deque

queue = deque(['spam', 'eggs'])
queue.append('strawberry')
queue.append('cashew')

print(queue.popleft())
print(queue.popleft())

