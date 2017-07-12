# Transpose and Swapping axes
import numpy as np

# numpy ndarray provides an attribute "T" which gives you the transpose of a matrix. Useful for 2darray's. For higher order matrices, it provides a transpose function which takes a tuple of axis numbers to permute the axes. There is also a function swapaxes() which also takes a pair of axis numbers. transpose() and swapaxes() parameters will make sense when you study matrices and determinants and study higher order matrices.

arr = np.arange(24).reshape(6,4)
print 'Original array\n %s' % arr
print 'arr.T\n %s' % arr.T
