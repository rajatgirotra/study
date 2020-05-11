import os
import sys
from collections import defaultdict

def print_lcs(b, X, i, j):
    if i == 0 or j == 0:
        return
    elif b[i][j] == 'd':
        print_lcs(b, X, i-1, j-1)
        print(X[i-1], end="")
    elif b[i][j] == 'u':
        print_lcs(b, X, i-1, j)
    else:
        print_lcs(b, X, i, j-1)

def lcs(x_arg, y_arg):
    # c[i][j] will hold the LCS(Xi, Yj)
    # b[i][j] will help construct the subsequence
    c = {key: defaultdict(dict) for key in range(len(X)+1)}
    b = {key: defaultdict(dict) for key in range(len(X)+1)}

    for i in range(len(X)+1):
        c[i][0] = 0
    
    for j in range(len(Y)+1):
        c[0][j] = 0

    for x in range(len(X)):
        i = x+1
        for y in range(len(Y)):
            j = y+1
            if X[x] == Y[y]:
                c[i][j] = 1 + c[i-1][j-1]
                b[i][j] = 'd' # diagnol
            elif c[i-1][j] >= c[i][j-1]:
                c[i][j] = c[i-1][j]
                b[i][j] = "u" # meaning up
            else:
                c[i][j] = c[i][j-1]
                b[i][j] = "l" # meaning left

#    for x in range(len(c.keys())):
#        print (x, c[x])

#    for x in range(len(b.keys())):
#        print (x, b[x])
    return c, b


if __name__ == "__main__":
    # prepare input
    # example 1
    #X = list('ABCBDAB')
    #Y = list('BDCABA')

    # example 2
    #X = list('10010101')
    #Y = list('010110110')

    # example 3
    X = list('ACCGGTCGAGTGCGCGGAAGCCGGCCGAA')
    Y = list('GTCGTTCGGAATGCCGTTGCTCTGTAA')

    c, b = lcs(X, Y)
    print('lcs({}, {} is {}'.format(X, Y, c[len(X)][len(Y)]))
    print('lcs = ', end=" ")
    print_lcs(b, X, len(X), len(Y))
    print()



