# given n eggs and k floor, find the critical floor from which the eggs break if dropped on the ground. Cannot
# let all eggs break before finding the critical floor

import os
import sys

def egg_drops(n, k):
    # enable this print statement to see how many times the function is called with same arguments.
    # print('egg_drops({},{}) called'.format(n,k))
    if n == 1:
        return k # no option but to drop from every floor one by one
    if k == 1:
        return 1 # if only one floor, we can drop from that floor
    if k == 0:
        return 0 # if no floors left, so return 0

    # otherwise there are 2 options; if you drop an egg from some floor x. 
    # case 1. it breaks. and you are left with n-1 eggs and x-1 floors
    # case 2. it doesnt break and you are left with n eggs and k-x floors.
    # we need to do this repeatedly for all x where x>=1 and x<=k
    min_egg_drops = None
    for x in range(1, k+1):
        drops = 1 + max(egg_drops(n-1, x-1), egg_drops(n, k-x))
        if min_egg_drops is None or drops < min_egg_drops:
            min_egg_drops = drops

    return min_egg_drops


if __name__ == "__main__":
    print(egg_drops(2, 10)) # 2 eggs, 10 floors

