import os
import sys

def edit_distance_dp(x, y):
    ed_matrix = []
    # create a 2d matrix to hold edit distances and initialize with 0
    for i in range(len(x)+1):
        ed_matrix.append([0] * (len(y)+1))

    # set base entries
    for i in range(len(x)+1):
        ed_matrix[i][0] = i
    for i in range(len(y)+1):
        ed_matrix[0][i] = i 

    for i in range(1, len(x)+1):
        for j in range(1, len(y)+1): 
            distHor = ed_matrix[i][j-1] + 1
            distVer = ed_matrix[i-1][j] + 1
            delta = 1 if x[i-1] != y[j-1] else 0
            distDiag = ed_matrix[i-1][j-1] + delta
            ed_matrix[i][j] = min(distHor, distVer, distDiag)

    return ed_matrix[-1][-1]


if __name__ == "__main__":
    x = sys.argv[1]
    y = sys.argv[2]
    print('Edit distance b/w %s and %s is %s' % (x, y, edit_distance_dp(x, y)))

