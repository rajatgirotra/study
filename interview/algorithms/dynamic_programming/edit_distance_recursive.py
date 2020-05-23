import os
import sys
import datetime as dt

# recursive implementation is very slow and wasteful. see value of n in output to see how many times
# the function gets called with the same arguments.
n = 0

def delta(x, y):
    return 0 if x == y else 1

def edit_distance(x, y):
    global n
    if x is None or len(x) == 0:
        return len(y)
    elif y is None or len(y) == 0:
        return len(x)
    else:
        if x == 'Compu' and y == 'compu':
            n += 1
        ed = min(edit_distance(x[:-1], y[:-1]) + delta(x[-1], y[-1]),
                edit_distance(x, y[:-1]) + 1, edit_distance(x[:-1], y) + 1)
        return ed

if __name__ == "__main__":
    # prepare input
    X = 'Computers'
    Y = 'compu ter'

    before = dt.datetime.now()
    ed = edit_distance(X, Y)
    after = dt.datetime.now()
    print('edit distance between {} and {} is {}'.format(X, Y, ed))
    print('edit distance took {} secs and n is {}'.format((after-before).total_seconds(), n))

