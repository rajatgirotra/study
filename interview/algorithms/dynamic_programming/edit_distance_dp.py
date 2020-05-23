import os
import sys
import datetime as dt
from collections import defaultdict

def delta(x, y):
    return 0 if x==y else 1

def edit_distance(x, y):
    # prepare 2D array of size len(x+1), len(y+1)
    # each entry will be the minimum edit_distance for the prefix of x and y till that index
    # example, m[3][3] will be edit_distance for x[0:3], y[0:3]

    # similarly s[3][3] will help you to construct the path
    len_x = len(x)
    len_y = len(y)
    m = dict()
    s = dict()
    for i in range(len_x+1):
        m[i] = defaultdict(dict)
        s[i] = defaultdict(dict)
        m[i][0] = i

    for i in range(len_y+1):
        m[0][i] = i

    for i in range(len_x):
        for j in range(len_y):
            d = m[i][j] + delta(x[i], y[j])
            l = m[i+1][j] + 1
            u = m[i][j+1] + 1
            m[i+1][j+1] = min(d, l, u)
            lowest = d
            lowest = l if lowest > l else lowest
            lowest = u if lowest > u else lowest
            if lowest == d:
                s[i+1][j+1] = "d"
            elif lowest == l:
                s[i+1][j+1] = "l"
            else:
                s[i+1][j+1] = "u"

    for i in range(len_x+1):
        print(s[i])
    return m[len_x][len_y], s


if __name__ == "__main__":
    # prepare input
    X = 'Shakespeare'
    Y = 'shake spear'

    before = dt.datetime.now()
    ed, ed_path = edit_distance(X, Y)
    after = dt.datetime.now()
    print('edit distance between {} and {} is {}'.format(X, Y, ed))
    print('edit distance took {} secs'.format((after-before).total_seconds()))


