# Indexing and Slicing

import numpy as np

# slicing, meaning take a sub array. Remember slicing a numpy array will always give you a view of the underlying array. To explicitly copy use the copy() function
arr = np.arange(10)
print('arr', arr)

arr_slice = arr[5:8] # return a view of elements from index 5 to 8
print ('Type of slice is %s' % type(arr_slice))
arr_slice[:] = 12  # assigning a scalar to a slice means propagate the value to every element of the slice.
print(arr)

# indexing. Think about this as:
#     [1,2,3]
#     [4,5,6]
#     [7,8,9]
# the rows are on axis 0 (AXIS 0 means rowwise) and columns are on axis 1(AXIS 1 MEANS COLUMN-WISE). we see more later on what axis are
arr = np.array([[1,2,3],[4,5,6],[7,8,9]])
print(arr.ndim)
print(arr[1,2]) # is same ias arr[1][2] but obviously this is more typing so [i,j] is preferred.

# slightly complex example
arr = np.array([[[1,2,3],[4,5,6]], [[7,8,9],[10,11,12]]])
print('Arr', arr)
print(arr.dtype)
print(arr.shape)
print(arr.ndim)
print(arr.size)

old_values = arr[0].copy() # arr[0] is a 2*3 matrix [[1,2,3],[4,5,6]]
print(type(old_values))
print(old_values.dtype)
print(old_values.shape)
print(old_values.ndim)
print(old_values.size)
arr[0] = 12
print(arr)
arr[0]= old_values # assigning an ndarray to another ndarray
print(arr)

# 2d slicing. Very trivial. 1darray behaves like a python list. So its easy to understand. With 2,3,4,.. ndarray you can specify multiple slices to get a view of the data you need.
arr = np.array([[1,2,3],
                [4,5,6],
                [7,8,9]])
arr_slice = arr[:, :1]   # for axis 0, take everything. ie all rows are included.
                         # for axis 1, take only the first column. So slice will return
                         # only the first element of each row
print(arr_slice)
print(arr_slice.ndim) # note that dimensions havent changed. It is still 2. So its still a 2darray
print(arr_slice.shape) # (3,1)
print(arr_slice.size) # 3

print(arr[2, :2]) # [2] gives u a 1darray and [:2] gives you [7,8] a 1d array
print(arr[1, 1:2]) # trivial [5]

# Lets try slicing on a 3darray, shape = (3,2,4)
array3d = np.array([[[1,2,3,4],
                     [5,6,7,8]],

                    [[9,10,11,12],
                     [13,14,15,16]],

                    [[17,18,19,20],
                     [21,22,23,24]]])

# how would you extract 10,11,14,15
arr_slice = array3d[1, :, 1:3] # [1] would give [[9,10,11,12],[13,14,15,16]], [:] would give the same thing, [1:3] would give 10, 11, 14, 15.
print(arr_slice)
print(arr_slice.ndim) # 2
print(arr_slice.shape) # (2,2)
print(arr_slice.size) # 4
