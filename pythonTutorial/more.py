#!/usr/bin/env python3

from collections import deque
q = deque(['a', 'b', 'c', 'd'])
print(q.popleft())

matrix = [
    [1,2,3,4],
    [0,0,0,0],
    [5,6,7,8],
    [-1,1,-2,2]
    ]

print(zip(*matrix))


l = [1,2,3,4];
print(list(zip(*l)))

