# the basic data structure in numpy as ndarray - an ndimensional data structure of homogenous data.

import numpy as np

# Creating a numpy array. Easiest way is to use np.array() function which takes a sequence like object (like list,
# set, list of list etc)
arr = np.array([1, 2, 3, 4, 5])
print(arr)

arr = np.array([1., 2., 3., 4., 5.])
print(arr)

# if you have nested lists of the same length, numpy will create a 2 dimensional array.
arr2d = np.array([[1, 2, 3], [4, 5, 6]])  # ndarray of (2,3) ie 2 rows and 3 cols.
print(arr2d)

# a numpy array has the following attributes
print('Size', arr2d.size)  # total number of elements
print('nDim', arr2d.ndim)  # total number of dimensions (1 for 1d array, 2 for 2d array etc)
print('Shape', arr2d.shape)  # Tuple of dimensions (x, y, z)
print('DataType',
      arr2d.dtype)  # the data type of the data held. we have many datatypes like np.int8/16/32/64, float16/32, string_, bool, unicode_, python object etc.

# np.array() takes an optional dtype (datatype) member which can be something
# like int64, uint8m float64 etc etc.
arr2d = np.array([[1, 2, 3], [4, 5, 6]], dtype='float64')
print('DataType-changed to', arr2d.dtype)

# create an array of all zeroes or ones
zeroes = np.zeros((3, 6))  # the parameter is a shape object will create a 3*6 array
print('Zeroes', zeroes)

ones = np.ones(5)  # will create a 1d array of 5 ones
print('Ones', ones)

# arange function - used to create a numpy array with range() like numbers
arr = np.arange(5)  # parameters are (start, end, step, dtype)
print('Arange %s, np.arange(5).shape %s' % (arr, arr.shape))  # [0 1 2 3 4]

# prefer np.linspace() over np.arange() as it is more accurate when step size is floating point.
arr = np.linspace(0, 6, num=21, dtype=np.float64) # generate 21 evenly spaced numbers between 0 and 6
print(arr)

arr = np.identity(3)  # create an identify matrix of size 3
print('Identity\n', arr)

arr = np.empty((2, 3, 3))  # will create an array with dummy/garbage values
print(arr)

# numpy has a function astype() which takes a dtype argument and
# creates a new array (always creates a copy) with the specified dtype
arr = np.array([1.2, 3.45, -2.3, 0, 100.982])
print(arr.dtype)
arrNew = arr.astype(np.int64)  # will truncate all decimals.
print(arrNew, arrNew.dtype)

arr = np.array(['1.2', '3.45', '-2.3', '0', '100.982'])
print(arr.dtype)
arrNew = arr.astype(np.float64)  # will convert from string to float
print(arrNew, arrNew.dtype)

# You can also create an ndarray of randomly distributed doubles using np.random.randn() function
# print(np.random.randn(2, 3))  # create an array with shape=(2,3)
# print(np.random.standard_normal((2, 3)))  # same as above but this one takes a tuple.
# This is no deprecated. Prefer to use the np.random.Generator.standard_normal() method.
rng = np.random.default_rng() # will create an object of the Generator class.
rng.standard_normal((2, 3))

# reshape - numpy provides a very handy function numpy.reshape(a, shape) which takes an ndarray as first parameter and reshapes it data according to the second shape parameter
np.reshape(np.arange(32), (8, 4))  # whill give a 8*4 ndarray, first parameter can be an ndarray of any dimension
