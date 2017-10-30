# There are many ways of indexing and slicing ndarray's. Let's see them in action

import numpy as np

# -------------------
# First way - SLICING
# -------------------
arr = np.random.randn(7, 4)  # random 7*4 array
print('Arr (7*4) \n%s' % arr)

# Giving a single index value for every dimension will yield a value.
value = arr[0][3]
print('\nArr[0][3] %s, type %s' % (arr[0][3], type(arr[0][3])))

# Leaving out one or more dimensions will yield a sub-dimensional array
print('\nArr[1] %s' % arr[1])

# SLICING - Slicing gives a view of the underlying array. Modifying a slice modified the underlying array.
arr_slice = arr[1:3]  # get rows with index 1 and 2.
print('\narr[1:3]\n %s' % arr_slice)
print('arr_slice.ndim %s, arr_slice.shape %s' % (arr_slice.ndim, arr_slice.shape))

arr_slice = arr[1:3, 1:4]
print('\narr[1:3, 1:4]\n %s' % arr_slice)
print('arr_slice.ndim %s, arr_slice.shape %s' % (arr_slice.ndim, arr_slice.shape))

# Note the difference in shape and ndim from above one, in the example below, ndim is 1
# and shape is (2,). Everytime you specify a single index for any dimension, ndim reduces by 1
arr_slice = arr[1:3, 0]
print('\narr[1:3, 0]\n %s' % arr_slice)
print('arr_slice.ndim %s, arr_slice.shape %s' % (arr_slice.ndim, arr_slice.shape))

# striding ie choosing non-contiguous slice
arr_slice = arr[0:7:3]  # means from 0 to 7, choose every row where index%3==0
print('\narr[0:7:3]\n %s' % arr_slice)
print('arr_slice.ndim %s, arr_slice.shape %s' % (arr_slice.ndim, arr_slice.shape))

# striding ie choosing non-contiguous slice
arr_slice = arr[0:7:3, ::2]
# means from 0 to 7, choose every row where index%3==0, and in that slice, choose every column where
# index%2==0
print('\narr[0:7:3, ::2]\n %s' % arr_slice)
print('arr_slice.ndim %s, arr_slice.shape %s' % (arr_slice.ndim, arr_slice.shape))

# Note that slices of arrays do not copy the internal array data but also
# produce new views of the original data.

# -------------------
# Second way - Index Arrays
# -------------------
# you can specify numpy array's or simple lists (or list like objects) as indexes too.
# Note that using arrays always returns a copy of the data instead of a view like in slicing.
arr = np.arange(10, 0, -1)  # from 10 to 1 reducing by 1 each time
print('\nArr\n%s' % arr)
print('\nArr[[3,3,1,7,-2]] %s' % arr[[3, 3, 1, 7, -2]])

# basically what is returned is an array of the same shape as the shape of the index specified.
# This makes very easy to add new rows and cols
arr_indexed = arr[np.array([[0, 1], [0, 1]])]
print('\narr[np.array([[0, 1], [0, 1]])]\n%s' % arr_indexed)

# ------------------------------------------------------
# Second way - Index Arrays with multidimensional arrays
# ------------------------------------------------------
# With multidimensional arrays, indexing with arrays is little trickier.
# Case 1 - When all index arrays have the same shape, and there is an index array specified for every
# dimension, the result is an array of the same shape as the index array, and the values correspond to
# the index set for each position in the index arrays. Example,
arr = np.arange(24).reshape(2, 3, 4)
print('\nArr\n%s' % arr)
arr_indexed = arr[np.array([0, 1, 1]), np.array([1, 2, 1]), np.array([1, 2, 3])]
# will give you an array of shape (3,) i.e. same as index array and values at indexes
# [0,1,1] [1,2,2] [1, 1, 3]
print('\narr[np.array([0, 1, 1]), np.array([1, 2, 1]), np.array([1, 2, 3])]\n%s' % arr_indexed)
print('shape', arr_indexed.shape)

# Case 2 - When all index arrays have the same shape, BUT there is an index array MISSING for some
# the last dimension, then the last dimension is assumed as ':'. So the result is an array of the shape
# similar to the index array (with the last dimension as the last dimension of the data array,
# and the values correspond to the index set for each position in the index arrays. Example,
arr_indexed = arr[np.array([0, 1, 1]), np.array([1, 2, 1])]
# will give you an array of shape (3, 4) i.e. same as index array and values at indexes
# [0,1,:] [1,2,:] [1, 1, :]
print('\narr[np.array([0, 1, 1]), np.array([1, 2, 1])]\n%s' % arr_indexed)
print('shape', arr_indexed.shape)


# ------------------------------------------------
# Fourth way - Combining Index Arrays with slicing
# ------------------------------------------------
# arr = np.arange(35).reshape(5, 7)
# print('\nArr\n%s' % arr)
# arr_indexed = arr[np.array([2, 3, 4]), 1:3]
# print('\narr[np.array([2, 3, 4]), 1:3]\n%s' % arr_indexed)
