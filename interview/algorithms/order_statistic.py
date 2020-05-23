import os
import sys
import random

def randomized_partition(arr, p, r, i):
    rand_index = random.randint(p, r)
    tmp = arr[r]
    arr[r] = arr[rand_index]
    arr[rand_index] = tmp

    pivot = arr[r]
    i = p-1
    for j in range(p, r):
        if arr[j] < pivot:
            i += 1
            tmp = arr[j]
            arr[j] = arr[i]
            arr[i] = tmp
    i += 1
    arr[r] = arr[i]
    arr[i] = pivot
    return i


def randomized_sel(arr, p, r, i):
    if p == r:
        return p
    else:
        q = randomized_partition(arr, p, r, i)
        if q == i:
            return i
        elif q < i:
            return randomized_sel(arr, q+1, r, i)
        else:
            return randomized_sel(arr, p, q-1, i)


def randomized_select(arr, i):
    # ith smallest is value at index i-1 in the sorted array
    index = randomized_sel(arr, 0, len(arr)-1, i-1)
    return arr[index]


if __name__ == "__main__":
    # prepare input
    arr = [random.randint(0, 100) for _ in range(15)]
    # arr = [34, 59, 21, 50, 78, 16, 55, 80, 8, 58, 26, 32, 93, 43, 54]
    print('input arr {}'.format(arr))
    val = randomized_select(arr, 5) # 5th smallest means value at index 4 in the sorted input
    print('5th smallest value is {}'.format(val))
    arr.sort()
    print('sorted arr {}'.format(arr))
    pass

