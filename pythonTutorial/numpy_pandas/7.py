# free or universal functions
import numpy as np

# What about operations you want to do an the array but there is no operator for it. Example, taking cuberoot, square root etc. numpy provides free functions in the numpy module for that. Example: np.sqrt, np.exp
# you have binary functions also which take two ndarrays and apply the operation binary operation element wise.
# example np.maximum(x, y)

arr = np.arange(24).reshape(6,4)
print('Original array\n %s' % arr)
print('arr.sqrt\n %s' % np.sqrt(arr))
print('arr.exp\n %s' % np.exp(arr))


arr1 = np.random.randn(9).reshape(3,3)
arr2 = np.random.randn(9).reshape(3,3)
print('Original array 1\n %s' % arr1)
print('Original array 2\n %s' % arr2)
print('np.maximum(arr1, arr2)\n %s' % np.maximum(arr1, arr2))
