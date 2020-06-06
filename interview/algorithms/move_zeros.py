# write a function to move all zeros in a list to the end. Must do in place and with minimal operations
# must also maintain the relative ordering of the non zero elements.

import os
import sys


def move_zeros(l: list):
    idx = 0
    for i in range(len(l)):
        if l[i] != 0:
            l[idx] = l[i]
            idx += 1
    for i in range(idx, len(l)):
        l[i] = 0
    return None

if __name__ == "__main__":
    l = [0, 1, 0, 2, 3, 0]
    move_zeros(l)
    print(l)

