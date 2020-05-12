import os
import sys

# bubble sort.
# 1st pass compare: (1,2), (2, 3), (3, 4).. (n-1, n) and put larger number at higher index
# 2nd pass compare: (1,2), (2,3), (3, 4).. (n-2, n-1)

def bubble_sort(arr):
    for i in range(len(arr)-1):
        for j in range(len(arr)-1-i):
            if arr[j] > arr[j+1]:
                tmp = arr[j]
                arr[j] = arr[j+1]
                arr[j+1] = tmp

if __name__ == "__main__":
    # prepare input
    arr = [5, 2, 4, 6, 1, 3]
    #arr = [31, 41, 59, 26, 41, 58]
    print('un-sorted array: {}'.format(arr))
    bubble_sort(arr)
    print('sorted array: {}'.format(arr))

