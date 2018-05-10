# fancy indexing
import numpy as np

# Fancy indexing means specifying a list as an index. The format is very handy when you want to select arbitrary rows/cols which are not necessarily contiguous.

arr = np.arange(32).reshape(8,4)
print ('Original array\n %s' % arr)

fancy_arr = arr[[4, 0, 7, 5]] # index along axis 0 (ie rows) will return you rows 4,0,8 and 5
print ('fancy arr[[4,0,7,5]]\n %s' % fancy_arr)

# providing multiple fancy indexes behave slighly differently
arr = np.arange(32).reshape(4,4,2) # a 3darray
print ('Original array \n%s' % arr)
fancy_arr = arr[[1,3],[0,2]] # will select (1, 0) and (3, 2) # basically a simple cross product
print ('fancy arr[[1,3],[0,2]] \n%s' % fancy_arr)
# You have already seen this in numpy_indexing_and_slicing. So should be trivial.
# Basically np provides a function np.ix_(), this function takes N 1-D arrays (basically python lists)
# and returns a tuple of numpy ndarrays, So np.ix_([1,3], [0, 2]) will return a
# tuple (ndarray([1,3]),ndarray([2,3])). So we can also use
# arr[np.ix_([1,3],[0,2])] to get the same result.

# if you really wanted the second index [0,2] to give you a rectangular slice from the output of the first index. Then do:
fancy_arr = arr[[1,3]][:, [0,2]] # will give you row 0 and 2 from the o/p of the first index. ie give values at (1,0), (1,2), (3,0), (3,2)
print ('fancy arr[[1,3]][:, [0,2]] based on o/p of first index\n%s' % fancy_arr)
