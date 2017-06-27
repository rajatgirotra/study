# Given an array of integers in the range -10000..10000 of minimum length 2 and max length 100000. A slice of 2 or more contiguous elements is the average of those elements. Find the slice of indexes P and Q which has the least average. Only return the starting index P.

# there is a mathemetical proof which we need to study, which proves that if we have a slice of length 3 or greater, then there must exist a smaller slice which has a lesser average. So we only need to consider slices of length 2 and 3.


import os
import sys

def min_slice(arr):
    min_avg = 10000*3 + 1 # average of 3 elements cannot be more than 10000
    pos = 0
    for i in range(len(arr)-2):
        avg_2 = float(arr[i] + arr[i+1])
        avg_3 = float(avg_2 + arr[i+2])
        avg_2 /= 2
        avg_3 /= 3
        if min_avg > min(avg_2, avg_3):
            pos = i
            min_avg = min(avg_2, avg_3)
    avg_2 = float(arr[-2] + arr[-1]) / 2
    if min_avg > avg_2:
        pos = len(arr) - 2
        min_avg = avg_2
    return (pos, min_avg) 



if __name__ == "__main__":
    print min_slice([4, 2, 2, 5, 1, 5, 8])
    print min_slice([-2, 3, 4, 0, -1, 6])
