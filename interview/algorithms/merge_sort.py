import os
import sys

def merge(arr, p, q, r):
    left_arr = arr[p:q+1]
    right_arr = arr[q+1:r+1]
    left_index = 0
    right_index = 0
    for k in range(p, r+1):
        if left_index >= len(left_arr):
            arr[k] = right_arr[right_index]
            right_index = right_index + 1
        elif right_index >= len(right_arr):
            arr[k] = left_arr[left_index]
            left_index = left_index + 1
        elif left_arr[left_index] <= right_arr[right_index]:
            arr[k] = left_arr[left_index]
            left_index = left_index + 1
        else:
            arr[k] = right_arr[right_index]
            right_index = right_index + 1

def merge_sort(arr, p, r):
    if p < r:
        q = int((p+r)/2)
        merge_sort(arr, p, q)
        merge_sort(arr, q+1, r)
        merge(arr, p, q, r)

if __name__ == "__main__":
    # prepare input
    #arr = [5, 2, 4, 7, 1, 3, 2, 6]
    arr = [3, 41, 52, 26, 38, 57, 9, 49]
    print('un-sorted array: {}'.format(arr))
    merge_sort(arr, 0, len(arr)-1)
    print('sorted array: {}'.format(arr))

