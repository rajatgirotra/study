# Vectorization

import numpy as np

# numpy arrays support vectorization, that means you can use arithmetic operations with two ndarrays of the same size and the operation will be applied elementwise, or you can use ndarray with a scalar and the operation will be applied to every element individually. You dont need to write any for loops for iterating over the array and individually
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
print('pow', arr**0.5)
