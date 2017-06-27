# given coins of denominations v(1), v(2), v(3)..., v(n) of some currency and an amount C, make change for that amount with minimum number of coins.
# 1 = v(1) < v(2) < v(3)... < v(n). Since v(1) is 1, you can always make change for any given amount. 

# Do not think the solution is as simple as calculating k=floor(C/v(n)), then calculating floor(C-k*v(n)/v(n-1)). Consider input [1,20,37] and amount = 60.

# the solution will be min(coins(C)) = min(coins(C-v(i))) + 1, ie the minimum number of coins needed to make change for C-v(i) where i is each denomination + 1 (this one coin). An DP solution using tabulation is simple

import os
import sys

def making_change(denominations, amount):
    assert isinstance(denominations, list), 'denominations attribute is not a list'
    denominations.sort()
    assert denominations[0] == 1, 'minimum denomation is %s, should be 1' % denomations[0]
    
    # create a 2d matrix, with as many rows as denominations and as many cols as the amount+1
    change = [ [0] * (amount+1) for _ in range(len(denominations))]

    # initilize the matrix
    for i in range(amount+1):
        change[0][i] = i # denomination of value 1
    for i in range(len(denominations)):
        change[i][0] = 0 

    for i in range(1, len(denominations)):
        for j in range(1, amount+1):
            if j % denominations[i] == 0:
                change[i][j] = j/denominations[i]
            else:
                change[i][j] = 1+min(change[i-1][j], change[i][j-1])

    return min([change[i][-1] for i in range(len(denominations))])


if __name__ == "__main__":
    print making_change([1, 20, 37, 50], 260)
