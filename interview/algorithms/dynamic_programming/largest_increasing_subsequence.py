import os
import sys

def largest_increasing_subsequence(seq):
    lis = list()
    len_lis = list()
    # lis[k] holds the largest increasing subsequence ending at index k
    if seq > 0:
        lis.append(0)
        len_lis.append(1)
        for i in range(1, len(seq)):
            lis.append(0)
            len_lis.append(0)
            for j in range(i):
                if seq[i] > seq[lis[j]]:
                    lis[i] = i
                    len_lis[i] = len_lis[j] + 1
                elif len_lis[j] > len_lis[i]:
                    lis[i] = lis[j]
                    len_lis[i] = len_lis[j]
    return lis, len_lis

if __name__ == "__main__":
    input_seq = [10, 22, 9, 33, 21, 50, 41, 60]
    lis, len_lis = largest_increasing_subsequence(input_seq)
    print('largest increasing subsequence length is {}'.format(len_lis[len(input_seq)-1]))
    print('lis is {}'.format(lis))
    print('lis_len is {}'.format(len_lis))

