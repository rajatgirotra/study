# Boolean indexing

import numpy as np

# Intersting stuff- Boolean Indexing
# You know already that ndarray supports vectorization. ndarray also works with comparison functions
# eg:
arr = np.random.randn(2,3)
print(arr)
print(arr<0) # this will return a boolean ndarray where each value will be True or False.
# such a boolean array can also be used as an index or for slicing.
# THE MOST IMPORTANT THING IS TO REMEMBER IS THAT THE LENGTH OF THE BOOLEAN NDARRAY SHOULD BE THE SAME AS THE AXIS YOU ARE INDEXING/SLICING.
# which means if you are indexing/slicing around axis 0 (ie row-wise then number of rows should be same in both data and the boolean array)
print(arr[arr<0]) #here we are indexing axis 0 (ie row-wise, so row length is 2). So in (arr<0) axis 0 ie row-wise also has length 2 (shape is (2,3)). So for every TRUE value in the (arr<0) ndarray, the corresponding value in arr is chosen and the result is a 1darray.


# let say you have a list of names
names = np.array(["Bob", "Will", "Joe", "Bob", "Henry", "Will", "Matt"])
print (names)
# then the scalar operation "==" will give us a Boolean array of True or False
bArr = (names=='Bob')  # bArr is of shape (7,)
print(bArr)
#lets now create a random array of size(7,4) using numpy.random.randn() function
ranArr = np.random.randn(7, 4)
print (ranArr)
print(ranArr[names=='Bob']) # boolean slicing again with axis = 0 ie row-wise. So length of rows is of bArr is 7 and shape of data is (7,4). So length of rows of data is 7. So the same boolean array of size (7,) is used to index each column of data.

# Now lets say we want to splice along axis = 0, ie rows, then we can use boolean indexing
# by passing the boolean array as the subscript operator to ranArr
data = ranArr[names=='Bob', :]  # this is called boolean indexing
print('Data', data)

# you can also do
data = ranArr[names != 'Bob']  # or ranArr[names != 'Bob']
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
