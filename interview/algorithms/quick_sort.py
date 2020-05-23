import os
import sys

def partition(arr, left_index, right_index):
    i = left_index - 1
    pivot = arr[right_index]
    for j in range(left_index, right_index):
        if arr[j] < pivot:
            i += 1
            tmp = arr[i]
            arr[i] = arr[j]
            arr[j] = tmp
    i += 1
    arr[right_index] = arr[i]
    arr[i] = pivot
    return i


def quick_sort_recursive(arr, left_index, right_index):
    if left_index < right_index:
        mid = partition(arr, left_index, right_index)
        quick_sort_recursive(arr, left_index, mid-1)
        quick_sort_recursive(arr, mid+1, right_index)

def quick_sort(arr):
    quick_sort_recursive(arr, 0, len(arr)-1)


if __name__ == "__main__":
    # prepare input
    arr = [2, 8, 7, 1, 3, 5, 6, 4]
    print('un-sorted array {}'.format(arr))
    quick_sort(arr)
    print('sorted array {}'.format(arr))

