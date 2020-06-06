# given n eggs and k floor, find the critical floor from which the eggs break if dropped on the ground. Cannot
# let all eggs break before finding the critical floor

import os
import sys
from collections import defaultdict

def egg_drops(n, k):
    # for a DP solution we will create a 2D array (ie table, ie tabulation ie bottom up approach) where
    # we will find the minimum drops for every combination of n and k.

    drops = {key : defaultdict(dict) for key in range(n+1)} # eggs are along y axis and floors are along x axis.
    for i in range(k+1):
        drops[0][i] = 0
        drops[1][i] = i # you have one egg here
    for i in range(n+1):
        drops[i][0] = 0
        drops[i][1] = 1

    for i in drops.keys():
        print(drops[i])

    for i in range(2, n+1):
        for j in range(2, k+1):
            drops[i][j] = max(drops[i-1][j-1], drops[i][

    return 0


if __name__ == "__main__":
    print(egg_drops(2, 10)) # 2 eggs, 10 floors

