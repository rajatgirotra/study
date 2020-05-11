import os
import sys
from collections import defaultdict

# matrix chain multiplication using dynamic programming using bottom up approach. ie.
# we first find m[1][2], m[2][3], m[3][4], etc.. and then finally m[1,6]
# this take O(n cube) time

def parenthesization_out(s, i, j):
    if i == j:
        print (' A-{} '.format(i), end="")
    else:
        print('(', end="")
        parenthesization_out(s, i, s[i][j])
        parenthesization_out(s, s[i][j] + 1, j)
        print(')', end="")

def min_matrix_mul_cost(p):
    matrix_count = len(p) - 1
    # m[i][j] = minimum no of scalar multiplications required to multiply matrix from matrix i to j
    # s[i][j] = contains the value k where i <= k < j, which results in minimum cost
    m = {k1: defaultdict(dict) for k1 in range(1, matrix_count+1)}
    s = {k1: defaultdict(dict) for k1 in range(1, matrix_count+1)}

    for i in range(1, matrix_count+1):
        m[i][i] = 0

    for skip in range(1, matrix_count):
        for i in range(1, matrix_count-skip+1):
            j = skip + i
            m[i][j] = 4294967295 # 2 to pwer 32 -1 (some very large number)
            for k in range(i, j):
                # print('computing m[{}][{}] for k = {}'.format(i,j,k))
                val = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]
                if val < m[i][j]:
                    m[i][j] = val
                    s[i][j] = k

    return m[1][matrix_count], s

if __name__ == "__main__":
    # prepare input (array of dimensions of matrices)
    # p = [30, 35, 15, 5, 10, 20, 25]
    p = [5, 10, 3, 12, 5, 50, 6]

    min_mul, parenthesization = min_matrix_mul_cost(p)
    print('min cost of matrix multiplication is {}'.format(min_mul))
    parenthesization_out(parenthesization, 1, len(p)-1)
    print()

