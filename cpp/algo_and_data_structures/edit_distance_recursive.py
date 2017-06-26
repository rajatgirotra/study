import os
import sys

def edit_distance_recurive(x, y):
    if len(x) == 0:
        return len(y) # the ED b/w an empty string and another string is the length of that string
    if len(y) == 0:
        return len(x)
    delta = 1 if x[-1] != y [-1] else 0
    return min(edit_distance_recurive(x[:-1], y[:-1]) + delta,
               edit_distance_recurive(x[:-1], y) + 1,
               edit_distance_recurive(x, y[:-1]) + 1)

if __name__ == "__main__":
    x = sys.argv[1]
    y = sys.argv[2]
    print('Edit distance b/w %s and %s is %s' % (x, y, edit_distance_recurive(x, y)))

