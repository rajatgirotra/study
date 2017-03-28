#!/usr/bin/env python

# the basic data structure in numpy as ndarray - an ndimensional data structure for homogenous data.

import numpy as np

# Creating a numpy array. Easiest way is to use np.array() function which takes a sequence like object
arr = np.array([1,2,3,4,5])
print(arr)

arr = np.array([1., 2., 3., 4., 5.])
print (arr)

arr2d = np.array([[1,2,3],[4,5,6]])
print(arr2d)

# a numpy array has the following attributes
print ('Size', arr2d.size)
print ('nDim', arr2d.ndim)
print ('Shape', arr2d.shape)
print ('DataType', arr2d.dtype)

# np.array() takes an optional dtype (datatype) member which can be something
# like int64, uint8m float64 etc etc.
arr2d = np.array([[1,2,3],[4,5,6]], dtype='float64')
print ('DataType-changed to', arr2d.dtype)

# create an array of all zeroes or ones
zeroes = np.zeros((3, 6))
print('Zeroes', zeroes)

ones = np.ones(5)
print('Ones', ones)

# arange function - used to create a numpy array with range() like numbers
arr = np.arange(5)
print('Arange', arr)  # [0 1 2 3 4]

arr = np.identity(3)  # create an identify matrix of size 3
print('Identity\n', arr)

arr = np.empty((2,3,3))  # will create an array with dummy/garbage values
print(arr)

# numpy has a function astype() which takes a dtype argument and
# creates a new array (always creates a copy) with the specified dtype
arr = np.array([1.2, 3.45, -2.3, 0, 100.982])
print(arr.dtype)
arrNew = arr.astype(np.int64)
print(arrNew, arrNew.dtype)

arr = np.array(['1.2', '3.45', '-2.3', '0', '100.982'])
print(arr.dtype)
arrNew = arr.astype(np.float64)
print(arrNew, arrNew.dtype)

# numpy arrays support vectorization, that means you can use arithmetic operations
# with two arrays of the same size and the operation will be applied elementwise
arr = np.array([1,2,3,4])
print('Addition', arr+arr)
arr = np.array([1,2,3,4])
print('Subtraction', arr-arr)
arr = np.array([1,2,3,4])
print('Multiply', arr*arr)

# similarly u can do scalar operations
arr = np.array([1,2,3,4])
print('Addition', arr+10)
print('Subtraction', arr-4)
print('Multiply', arr*0.5)
print('Division', 1/arr)

# slicing, meaning take a sub array. Remember slicing a numpy array will always
# give you a view of the underlying array. To explicitly copy use the copy() function
arr = np.arange(10)
print('arr', arr)

arr_slice = arr[5:8] # return a view of elements from index 5 to 8
arr_slice[:] = 12
print(arr)

# indexing. Think about this as:
#     [1,2,3]
#     [4,5,6]
#     [7,8,9]
# the rows are on axis 0 and cloumns are on axis 1. You see more later on what axis are
arr = np.array([[1,2,3],[4,5,6],[7,8,9]])
print(arr.ndim)
print(arr[1,2]) 

# slightly complex example
arr = np.array([[[1,2,3],[4,5,6]], [[7,8,9],[10,11,12]]])
print('Arr', arr)
print(arr.dtype)
print(arr.shape)
print(arr.ndim)
print(arr.size)

old_values = arr[0].copy() # arr[0] is a 2*3 matrix
print(type(old_values))
print(old_values.dtype)
print(old_values.shape)
print(old_values.ndim)
print(old_values.size)
arr[0] = 12
print(arr)
arr[0]= old_values
print(arr)

# 2d slicing. Very trivial
arr = np.array([[1,2,3],[4,5,6],[7,8,9]])
print(arr[:, :1])  # for axis 0, take everything. ie all rows are included.
                   # for axis 1, take only the first column. So slice will return
                   # only the first element of each row
print(arr[2, :2])
print(arr[1, 1:2])

# Intersting stuff- Boolean Indexing
# let say you have a list of names
names = np.array(["Bob", "Will", "Joe", "Bob", "Henry", "Will", "Matt"])
# tehn the scalar operation "==" will give us a Boolean array of True or False
bArr = (names=='Bob')
print(bArr)
#lets now create a random array of size(7,4) using numpy.random.randn() function
ranArr = np.random.randn(7, 4)
print (ranArr)
# Now lets say we want to splice along axis = 0, ie rows, then we can use boolean indexing
# by passing the boolean array as the subscript operator to ranArr
data = ranArr[names=='Bob', :]  # this is called boolean indexing
print('Data', data)
# the main requirement is the axis along which you are slicing must have the same numbers
# of entries as the boolean array. In this case that number id 7. So only rows 0 and 3
# are filtered out.

# you can also do
data = ranArr[-(names == 'Bob')]  # or ranArr[names != 'Bob']
print('Data', data)

# or
data = ranArr[(names == 'Joe') | (names=='Matt')]
print('Data', data)

# NOTICE SOMETHING, WHEN SLICING USING BOOLEAN INDEXING, numpy will create a copy of the array.
data[0] = 0
print('Data', data)
print('ranArr', ranArr)

# Some more magic
data = np.random.randn(7,4)
print('Data')
print(data)
newData = (data < 0)
print(newData.dtype)
print(newData)
# so now you can use boolean indexing on the whole data array
data[data < 0] = 0
print('Zeroed data')
print(data)
