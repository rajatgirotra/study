#!/usr/bin/env python3

# A pandas Series is a one dimensional array object in which each item can be given a label. These labels
# are specified as the "index" parameter when creating a Series.
import numpy as np
from pandas import Series
import pandas as pd

#  Three ways are available in which you can create a Series object
#  One: create using a numpy ndarray (n-dimensional array). np.random.randn(5) returns a ndarray with random values
#  Since the index parameter (labels) are missing, default is to give label names starting from 0, 1, 2, and so on. 
s = Series(np.random.randn(5))
print(s)

# Optionally you can specify labels yourself
# create a convinience function first
randn = np.random.randn
s = Series(randn(6), index = ['Raj','Vid','S','J','A','Nhj1'])
print(s)

# you can also give a name to your Series
s = Series(randn(6), index = ['Raj','Vid','S','J','A','Nhj1'], name = 'MySeries')
print(s)


## Option 2: using dictionary. Here if index argument is omitted, then the key values become
## the labels. eg:
dic = { 'a':-8892.22, 'busy':0, 'fever': 123}
s = Series(dic)
print(s)

## Otherwise you can specify index yourself. Here if a label in index matches
## a key in dict, it will be used, otherwise there will be new entries in the Series
## with all those list items for which there is no key in the dict and the series value
## be NaN (not a number). NaN is the standard missing data marker.
s = Series(dic, index = ['a', 'b', 'c', 'd', 'e', 'f'])
print(s)

# Three. Using a scalar value. In this case, index must be provided
# The Series will have the same scalar value for all items
s = Series(10, index = [x for x in range(5)])
print (s)

#### Usin Series
###############

s = Series(np.random.randint(0,7,size=10), index = ['a','b','c','d','e','f','g','h','i','j'])
print(s)

## Indexing, 
print(s[0], end='')
print(' is same as ', end='')
print(s['a'], end='')
print(' which is same as ', end='')
print(s.a)

# A lot of Numpy functions also accept Series as arguments without problems

# Some useful functions
# Series.median(axis=None, skipna=None, level=None, numeric_only=None, **kwargs),
    # axis is either 0 or 1. axis = 0 means 'column-wise' and axis = 1 means 'row-wise'
    # as of nowm, we know that a series is a 1D array, so only axis = 0 makes-sense
    # if you put axis = 1, then you get an error as it doesnt make sense for a 1D array
    # Check for yourself.
    # skipna = skip NA/null values. If everything in the series is NA, return NA
    # level = dont know yet
    # numeric_only = currently not implemented
s.sort()
print(s)
print(s.median(axis=0)) # median means first sort , then middle element. For even no of entries, average of two items in the middle.
#print(s.median(axis=1))

# Comparing whole list with a scalar 
l = (s > s.median()) # this compares every item in the list with the scalar and returns a list of bool
print(l)
print(s[l]) ## This will print only those items where the corresponding item in list is True. So elegant . Remember it.. :-)

#Series can take a list of indexes to print (0,1,2 etc) or labels('a','d' etc) or even booleans as you saw above.
print(s[[3,4,1]])
print(s[['a','d']])

# like in a python dictionary, in Series also you can say
print('b' in s)
print('z' in s)

p = s.get('x')
print(p)

#Or

p = s.get('x', np.nan)
print(p)

# Other scalar operation on list
s = s*2
print(s)

s = s+s
print(s)

s = s[2:] + s[:] # Here since the first series starts from index 2, there will be no corresponding labels available for the second series
# So these will not be added. and the resultant series will show NaN. Basically in a nutshell series are combined on the basis of
# labels and where labels are absent operation is a Nan
print(s)

# will drop rows from Series (both label and value) where value is NaN.
s = s.dropna()
print(s)

#value_counts
# Series.value_counts(normalize=False, sort=True, ascending=False, bins=None, dropna=True)
# returns a Series of objects and their respective counts. By Default also sort them in descending order
# and drops (removes objects which are NaN).

# fillna
# The interface and arguments to fillna look very puzzling and complex. For now just remember you can replace all NaN in Series using
# this function.
s = Series(np.random.randint(0,10,size=10), index = [x for x in range(10)])
print(s)
s[2] = np.nan
s[5] = np.nan
print(s)
s=s.fillna('Some value')
print(s)

# Guess whats going on here. I was expecting you'll know this
# Simple we are comparing series with a scalar. So it compares the scalar with each item
# in series and returns a list of boolean True or False
print(s=='Some value')
##Very elegant way of assining different values to different items at the same time.
## Infact we can also set the same value if we want.
s[s=='Some value'] = [2,5]
print(s)

# At this point you can go to matplotlib folder and read 1_README and 2_plots.py
# Afterwards read ex2.py
