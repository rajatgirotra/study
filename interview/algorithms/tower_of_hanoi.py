import os
import sys

# print all moves of tower of hanoi using recursion. Running time is O(pow(2, n))

def tower_of_hanoi_moves(arg, f, t, a): # f: from_peg, t: to_peg, a: aux_peg
    if arg == 1:
        print('move disk {} from peg {} to {}'.format(1, f, t))
    else:
        tower_of_hanoi_moves(arg-1, f, a, t)
        print('move disk {} from peg {} to {}'.format(arg, f, t))
        tower_of_hanoi_moves(arg-1, a, t, f)


def tower_of_hanoi(arg):
    from_peg = 'A'
    to_peg = 'B'
    aux_peg = 'C'
    tower_of_hanoi_moves(arg, from_peg, to_peg, aux_peg)


if __name__ == "__main__":
    # 4 is the number of disks that we want to move from one peg/stick to another using an intermediate peg/stick
    tower_of_hanoi(int(sys.argv[1]))

