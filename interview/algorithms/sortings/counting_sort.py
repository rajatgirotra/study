import os
import sys

# assume all elements in arr are <= len(arr)
def counting_sort(arr):
    # maintain a count of each element in the array
    aux_arr = [0 for _ in range(len(arr)+1)] # len(arr) == 8, len(aux_arr) = 9
    for i in range(len(arr)):
        aux_arr[arr[i]] += 1

    # aux_arr[index] contains the number of times index is present in arr

    # modify aux_arr so that value of each index contains the nunber of items equal to index or less than that
    for i in range(1, len(aux_arr)):
        aux_arr[i] += aux_arr[i-1]

    # print aux arr for debugging
    print('aux_arr {}'.format(aux_arr))

    # create the target arr now
    target_arr = [None] * len(arr)
    for i in range(len(arr)-1, -1, -1):
        aux_arr[arr[i]] -= 1
        target_arr[aux_arr[arr[i]]] = arr[i]
    return target_arr


if __name__ == "__main__":
    # prepare input
    arr = [2, 5, 3, 0, 2, 3, 8, 3]
    print('un-sorted array {}'.format(arr))
    arr = counting_sort(arr)
    print('sorted array {}'.format(arr))

