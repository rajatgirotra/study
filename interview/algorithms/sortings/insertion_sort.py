import os
import sys

def insertion_sort(arr):
    for i in range(1, len(arr)):
        pivot = arr[i]
        j = i-1
        while j>=0 :
            if arr[j] > pivot:
                arr[j+1] = arr[j]
                j = j - 1
            else:
                break

        arr[j+1] = pivot

if __name__ == "__main__":
    # prepare input
    #arr = [5, 2, 4, 6, 1, 3]
    arr = [31, 41, 59, 26, 41, 58]
    insertion_sort(arr)
    print('sorted array: {}'.format(arr))

