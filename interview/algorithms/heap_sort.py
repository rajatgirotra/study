import os
import sys


def parent(i):
    return int((i-1)/2)

def left(i):
    return 2*i + 1

def right(i):
    return 2*i + 2

def max_heapify(arr, index, heap_size):
    left_index = left(index)
    right_index = right(index)
    largest = index
    if heap_size > left_index and arr[left_index] > arr[index]:
        largest = left_index
    if heap_size > right_index and arr[right_index] > arr[largest]:
        largest = right_index

    if largest != index:
        tmp = arr[largest]
        arr[largest] = arr[index]
        arr[index] = tmp
        max_heapify(arr, largest, heap_size)


def build_max_heap(arr):
    heap_size = len(arr)
    index = int(len(arr)/2)-1
    while True:
        if index < 0:
            break
        else:
            max_heapify(arr, index, heap_size)
            index = index - 1
  

def heap_sort(arr):
    build_max_heap(arr)
    heap_size = len(arr)
    for i in range(len(arr)-1, 0, -1):
        tmp = arr[i]
        arr[i] = arr[0]
        arr[0] = tmp
        heap_size = heap_size - 1
        max_heapify(arr, 0, heap_size)


if __name__ == "__main__":
    # prepare input
    arr = [4, 1, 3, 2, 16, 9, 10, 14, 8, 7]
    #arr = [5, 13, 2, 25, 7, 17, 20, 8, 4]

    print('un-sorted array {}'.format(arr))
    heap_sort(arr)
    print('sorted array {}'.format(arr))

