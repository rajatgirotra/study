# Broadcasting are certain rules which apply to arrays of different shapes when doing arithmetic operations.
# When operating on two arrays, NumPy compares their shapes element-wise. It starts with the trailing dimensions,
# and works its way forward. Two dimensions are compatible when
# they are equal, or
# one of them is 1. Lets see some examples

import numpy as np

arr3d = np.arange(12).reshape(2, 2, 3)
arr1d = np.array[0, 1, 2]
# 2  2  3
#       3
# We start with the trailing dimensions, since they match, broadcasting takes place and arr1d applies to all
# the rows in the arr3d.

# A      (4d array):  8 x 1 x 6 x 1
# B      (3d array):      7 x 1 x 5
# Result (4d array):  8 x 7 x 6 x 5

# A      (2d array):  5 x 4
# B      (1d array):      1
# Result (2d array):  5 x 4
#
# A      (2d array):  5 x 4
# B      (1d array):      4
# Result (2d array):  5 x 4
#
# A      (3d array):  15 x 3 x 5
# B      (3d array):  15 x 1 x 5
# Result (3d array):  15 x 3 x 5
#
# A      (3d array):  15 x 3 x 5
# B      (2d array):       3 x 5
# Result (3d array):  15 x 3 x 5
#
# A      (3d array):  15 x 3 x 5
# B      (2d array):       3 x 1
# Result (3d array):  15 x 3 x 5

# A      (1d array):  3
# B      (1d array):  4 # trailing dimensions do not match
#
# A      (2d array):      2 x 1
# B      (3d array):  8 x 4 x 3 # second from last dimensions mismatched

# Broadcasting provides a convenient way of taking the outer product (or any other outer operation) of two arrays.
# The following example shows an outer addition operation of two 1-d arrays:

a = np.array([0.0, 10.0, 20.0, 30.0])
b = np.array([1.0, 2.0, 3.0])
print(a[:, np.newaxis] + b)

# Here the newaxis index operator inserts a new axis into a, making it a two-dimensional 4x1 array.
# Combining the 4x1 array with b, which has shape (3,), yields a 4x3 array.
