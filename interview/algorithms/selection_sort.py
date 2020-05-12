import os
import sys

# selection sort.
# 1st pass compare: (1,2), (1, 3), (1, 4).. and put lowest on 1st pos
# 2nd pass compare: (2,3), (2, 4), (2, 5).. and put lowest on 2nd pos

def selection_sort(arr):
    for i in range(len(arr)-1):
        for j in range(i+1, len(arr)):
            if arr[i] > arr[j]:
                tmp = arr[i]
                arr[i] = arr[j]
                arr[j] = tmp

if __name__ == "__main__":
    # prepare input
    arr = [5, 2, 4, 6, 1, 3]
    arr = [31, 41, 59, 26, 41, 58]
    print('un-sorted array: {}'.format(arr))
    selection_sort(arr)
    print('sorted array: {}'.format(arr))

