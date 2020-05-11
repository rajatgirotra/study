import os
import sys
from collections import defaultdict

# matrix chain multiplication using recursion and memoization. this will take considerable less time as we
# avoid computing subproblems again.

def parenthesization_out(s, i, j):
    if i == j:
        print (' A-{} '.format(i), end="")
    else:
        print('(', end="")
        parenthesization_out(s, i, s[i][j])
        parenthesization_out(s, s[i][j] + 1, j)
        print(')', end="")

def lookup_chain(p, i, j):
    if m[i][j] != 4294967295:
        return m[i][j]
    if i == j:
        m[i][j] = 0
    else:
        for k in range(i, j):
            val = lookup_chain(p, i, k) + lookup_chain(p, k+1, j) + p[i-1]*p[k]*p[j]
            if val < m[i][j]:
                m[i][j] = val
                s[i][j] = k
    return m[i][j]


# first call to this function will be memoized_matrix_chain(p)
def memoized_matrix_chain(p):
    for i in range(1, matrix_count + 1):
        m[i] = dict()
        s[i] = dict()
        for j in range(1, matrix_count + 1):
            m[i][j] = 4294967295 # 2 to pwer 32 -1 (some very large number)
            s[i][j] = 0
    lookup_chain(p, 1, len(p)-1)
    

if __name__ == "__main__":
    # prepare input (array of dimensions of matrices)
    p = [30, 35, 15, 5, 10, 20, 25]
    p = [5, 10, 3, 12, 5, 50, 6]
    matrix_count = len(p) - 1

    # m[i][j] = minimum no of scalar multiplications required to multiply matrix from matrix i to j
    # s[i][j] = contains the value k where i <= k < j, which results in minimum cost
    m = dict()
    s = dict()

    memoized_matrix_chain(p)
    print('min cost of matrix multiplication is {}'.format(m[1][matrix_count]))
    parenthesization_out(s, 1, matrix_count)
    print()


