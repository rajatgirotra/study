# pandas Series and DataFrame

import numpy as np
import pandas as pd

# A series is very similar to a numpy ndarray except that it has labels for every item. The labels are collectively called index and can be accessed by the index attribute. Series object can also be given a name using the "name" parameter in the ctor. Also you can specify the data type using dtype parameter.

# Making a series object
# WITH LIST
s = pd.Series([1., 2., 3., 4.], name='MySeries') # by default index labels are 0,1,2,3...
print (s)

# With DICT
s = pd.Series({'a': 1, 'b': 2, 'c': 3}) # be default, index will be dict keys. We can specify index explicitly also in which case only those value are taken from the dict
print s
s = pd.Series({'a': 1, 'b': 2, 'c': 3}, index=['a','c']) 
print s

# With NDARRAY
s = pd.Series(np.random.rand(5), index=['i1', 'i2', 'i3', 'i4', 'i5'])
print (s)

# With scalar
s = pd.Series(5, index=['a', 'b', 'c']) # repeats 5 for each index.
print s

# Usage: Series can be used at almost all places where ndarray can be used. Series supports indexing, slicing, boolean indexing, fancy indexing.
print 'slicing', s[:3] # slicing
print 'indexing', s[2] # indexing
print 'boolean indexing', s[s>s.median()] # boolean indexing
print 'fancy indexing', s[[1,2]] # fancy indexing

# Series also behaves like a dict
print 'i2 in s %s' % ('i2' in s)
try:
    print s['i7'] # KeyError. use s.get('i7') which return None
except KeyError as e:
    print 'Error %s' % e

print 's.get(i7) is %s' % s.get('i7')
print 's.get(i7, np.nan) is %s' % s.get('i7', np.nan)


# Vector operations
print '2s %s' % (s+s)
print 's*2 %s'% s*2
print 'np.exp(s) %s' % np.exp(s)
print 'np.sqrt(s) %s' % np.sqrt(s)
