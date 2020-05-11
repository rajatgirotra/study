import os
import sys
from collections import defaultdict

# matrix chain multiplication using recursion. this will take exponential time.

def parenthesization_out(s, i, j):
    if i == j:
        print (' A-{} '.format(i), end="")
    else:
        print('(', end="")
        parenthesization_out(s, i, s[i][j])
        parenthesization_out(s, s[i][j] + 1, j)
        print(')', end="")

# first call to this function will be matrix_chain_recursive(s, 1, matrix_count)
def matrix_chain_recursive(p, i, j):
    # return 0 when i == j
    if i == j:
        return 0
    else:
        # assign a very large number to m[i][j] to start with
        m[i][j] = 4294967295 # 2 to pwer 32 -1 (some very large number)
        for k in range(i, j): # ie for all k where i <= k < j
            val = matrix_chain_recursive(p, i, k) + matrix_chain_recursive(p, k+1, j) + p[i-1]*p[k]*p[j]
            if val < m[i][j]:
                m[i][j] = val
                s[i][j] = k
        return m[i][j]

if __name__ == "__main__":
    # prepare input (array of dimensions of matrices)
    p = [30, 35, 15, 5, 10, 20, 25]
    # p = [5, 10, 3, 12, 5, 50, 6]

    matrix_count = len(p) - 1
    # m[i][j] = minimum no of scalar multiplications required to multiply matrix from matrix i to j
    # s[i][j] = contains the value k where i <= k < j, which results in minimum cost
    m = {k1: defaultdict(dict) for k1 in range(1, matrix_count+1)}
    s = {k1: defaultdict(dict) for k1 in range(1, matrix_count+1)}

    matrix_chain_recursive(p, 1, matrix_count)
    print('min cost of matrix multiplication is {}'.format(m[1][matrix_count]))
    parenthesization_out(s, 1, matrix_count)
    print()


