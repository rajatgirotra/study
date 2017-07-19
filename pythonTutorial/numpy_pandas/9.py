# DataFrame: Think of a data frame as a sequence of series (where each series is arranged vertically). So it looks like a excel spreadsheet or 2 dimensional data.

import numpy as np
import pandas as pd
from pandas import DataFrame

# creating DataFrame from dict of Series or dict of dicts.
# dictionary keys are column headings (so 'a' and 'b' are columns headings), the nested dictionary is converted to
# series with data as 'a' and 'b' and index as 0 and 1. Very trivial
d = {'a': pd.Series(np.random.randn(5)), 'b': { 0: 'a', 1: 'b'}}
df = DataFrame(d)
print 'df from dict of series/dict \n%s\n' % df
# if you want 'a' and 'b' (dict keys) to become row index instead. use DataFrame.from_dict() function with the orient parameter
df = DataFrame.from_dict(d, orient='index')  # 'a' and 'b' will be row labels. columns will be 0, 1, 2, 3, 4
print 'df from DataFrame.from_dict(orient=index) \n%s\n' % df

# from dict of lists
d = {'one': [1., 2., 3., 4.], 'two': [4, 3, 2, 1]} # columns are 'one' and 'two'
df = DataFrame(d, index=['a', 'b', 'c', 'd'])
print 'df from dict of lists (almost same as above) \n%s\n' % df

# from list of dicts
d = [{'a': 1, 'b': 20}, {'a': 1., 'b': 2., 'c': 20.}] # columns will be 'a', 'b', 'c'
df = DataFrame(d)
print 'df from list of dict \n%s\n' % df

# from structure. When your data is in a structured format, like a tuple of values making a row, then you use this ctor
# 'A', 'B', 'C' are column names, i4, f8 and ? are type codes defined in numpy. i4 means 4 byte integer, f8 is 8 byte float, ? means bool. argument to np.zeros is as many structures you want to define. ie as many rows.
data = np.zeros((2,), dtype=[('A', 'i4'), ('B', 'f8'), ('C', '?')])
data[:] = [(1, 3., False), (10, 9.3466, True)]
df = DataFrame(data)
print 'df from structure \n%s\n' % df

# let say in the above example, you want to create an index from one of the columns (let say column C (bool)), then you can do that using the from_records ctor
data = np.array([(1, 3., False), (10, 9.3466, True)], dtype=[('A', 'i4'), ('B', 'f8'), ('C', '?')])
df=DataFrame.from_records(data, index='C')
print 'df from pd.DataFrame.from_records \n%s\n' % df



# DataFrame also supports multi indexed (multi columns, multi rows)
# from dict of tuples
data = {('a', 'a'): {('A', 'B'): 1, ('A', 'C'): 6, ('A', 'A'): np.nan, ('D', 'D'): -1},
         ('a', 'b'): {('A', 'B'): 2, ('A', 'C'): 7, ('D', 'D'): -2},
         ('a', 'c'): {('A', 'B'): 3, ('A', 'C'): 8},
         ('b', 'a'): {('A', 'B'): 4, ('A', 'C'): 9},
         ('b', 'b'): {('A', 'B'): 5, ('D', 'D'): -5}}
df=DataFrame(data)
print 'df (multi index) from dict of tuples \n%s\n' % df

# from DataFrame.from_items(arg) used when arg is a list of two tuple (x, y): x is column name(or row name if orient='index') and y is a list of column (or row) values
df=DataFrame.from_items([('A', [1, 2, 3]), ('B', [4, 5, 6])])
print 'df from list of two tuple using from_items()\n%s\n' % df
# with orient='index'
df=DataFrame.from_items([('A', [1, 2, 3]), ('B', [4, 5, 6])], orient='index', columns=['un', 'dos', 'tres'])
print 'df from list of two tuple using from_items(orient=index)\n%s\n' % df
