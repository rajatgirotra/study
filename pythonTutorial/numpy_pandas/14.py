import pandas as pd
import numpy as np
from pandas import DataFrame

# DataFrame.reindex is used to add/remove new indexes or columns.
df = DataFrame(np.arange(9).reshape(3, 3), index=['a', 'c', 'd'],
               columns=['Ohio', 'Texas', 'California'])
print('\ndf\n%s' % df)

# reindex is used to add/remove indexes.
# example, data for row 'd' and col 'Texas' will be removed.
# data for row 'd' and col 'Utah' will be NaN.
print('\ndf.reindex\n%s' % df.reindex(index=list('abc'), columns=['Ohio', 'Utah', 'California']))
print('\ndf.reindex\n%s' % df.reindex(index=list('abc'), columns=['Ohio', 'Utah', 'California'], fill_value='missing'))

# method parameter is used to interpolate missing values. Valid options are ffill, bfill, nearest.
# Remember that both index and columns should be sorted for interpolation to work
states = ['Ohio', 'Utah', 'California']
print('\ndf.reindex with method\n%s' % df.reindex(index=['a', 'b', 'c', 'd'], method='ffill',  # ffill is forward fill
                                                  columns=states.sort()))

# Dropping columns and rows is very trivial
print('\ndf.drop(Ohio, axis=1)\n%s' % df.drop('Ohio', axis=1))  # will drop column
print('\ndf.drop([a,c] index=1)\n%s' % df.drop(['a', 'c'], axis=0))  # will drop rows a & c

# Vectorized operations like adding, subtracting, multiplying, dataframes can be done either like
# df1 + df2 or df1.add(df2, kwargs) if we want more control, like how to treat NaN, or missing data etc.

# Operation b/w df and series
# Let say you have df of shape (7, 4) and a series of shape (7,)
df = DataFrame(np.arange(12.).reshape(3, 4))
print('\ndf\n%s' % df)
s = df.loc[0]
print('\ndf.loc[0]\n%s' % s)
print('df.loc[0].shape', s.shape)  # (4,) ndim = 1
df = df - s
# 3  4
#    4
# So broadcasting will apply and result will be (3, 4). By default, the index of series [0,1,2,3] aligns with columns
# of dataframe and then the operation takes place along the rows
print('\ndf-df.loc[0]\n%s' % df)

df = DataFrame(np.arange(12.).reshape(3, 4), index=list('abc'), columns=['Utah', 'Texas', 'California', 'Ohio'])
print('\ndf\n%s' % df)
s = pd.Series([0, 1, 2, 3], index=['Utah', 'NewYork', 'Texas', 'Ohio'])
print('\ndf.loc[a]\n%s' % s)
print('df.loc[a].shape', s.shape)  # (4,) ndim = 1
df = df + s  # note that as before index of series aligns with cols of data frame. So index and cols will me union together
# and for NewYork and California, entries will be NaN.
print('\ndf+df.loc[a]\n%s' % df)

# Apply function can be used to apply a callable on either axis (0 or 1). The result of a callable can be a scalar or
# a series. Let's see it in action
frame = DataFrame(np.random.randn(3, 4), index=list('abc'), columns=['NewDelhi', 'Mumbai', 'Bengaluru', 'Gurgaon'])
print('\nframe\n%s' % frame)
# Get average of every column
x = frame.apply(lambda x: x.mean(), axis=0)
print('\nframe.apply(axis=0)\n%s' % x)

# Get max-min of every row
x = frame.apply(lambda x: x.max() - x.min(), axis=1)
print('\nframe.apply(axis=1)\n%s' % x)


# get max, min for every column.
def f(x):
    return pd.Series([x.max(), x.min()], index=['max', 'min'])

x = frame.apply(f, axis=0)
print('\nframe.apply(axis=0)\n%s' % x)

# get max, min for every row.
def f(x):
    return pd.Series([x.max(), x.min()], index=['max', 'min'])

x = frame.apply(f, axis=1)
print('\nframe.apply(axis=1)\n%s' % x)

# You also have applymap. apply() applies to a complete row or column ie on an axis, whereas
# applymap() applies on every individual cell value

format = lambda x: '%.2f' % x
x = frame.applymap(format)
print('\nframe.applymap()\n%s' % x)

# Sorting and ranking
frame = DataFrame(np.random.randn(4, 3), index=['x', 'p', 'a', 'h'], columns=['Hawaii', 'Portugal', 'Manila'])
frame.sort_index()  # will be default with axis = 0. ie rows will be sorted based on frame.index
print('\nframe.sort_index()\n%s' % frame.sort_index())

# to sort based on column names, use axis = 1
print('\nframe.sort_index(axis=1, ascending=False)\n%s' % frame.sort_index(axis='columns', ascending=False))

# to sort rows based on values in a column instead, use sort_values(by=[])
print('\nframe.sort_values(axis=0, by=[])\n%s' % frame.sort_values(axis='index', by=['Hawaii', 'Manila']))

# series is sorted using the sort_values() and sort_index() api too
obj = pd.Series([4, np.nan, 7, np.nan, -3, 2])
print('\nseries.order(na_position=first)\n%s' % obj.sort_values(na_position='first'))
