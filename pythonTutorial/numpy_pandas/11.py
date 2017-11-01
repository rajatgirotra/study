# pandas indexing and column and row selection

import numpy as np
import pandas as pd
from pandas import DataFrame


# random dataframe
df = DataFrame(np.random.randn(3,4), columns=list('ABCD'), index=['one', 'two', 'three'])
print('df \n%s\n' % df)


# indexing rows
# very important. Use df.loc['row_label'] or df.iloc[row_index] to get a row. When you get a single row; you get a series. The index of this series is naturally the column names. So columns become the index (labels) of the series.
s = df.iloc[0] # the columns of df will become the index of s
print('row 0 of df \n%s\n' % s)
s = df.loc['two']
print('row two of df \n%s\n' % s)

s = df.loc[['one', 'two']]  # similary we have the iloc function df.iloc[[0, 1, 2]]
print('get two or more rows be specifying a list of labels \n%s\n' % s)

# Slice to get multiple rows. In Series and DataFrame, slicing inside [] slices rows as it is a very common operation.
print('row slices using index numbers df[0:2] \n%s\n' % df[0:2]) # or df.iloc[0:2] as shown below
print('row slices using index numbers df.iloc[0:2] \n%s\n' % df.iloc[0:2])
print('row slices using index labels df["one":"two"] \n%s\n' % df["one":"two"])

bool_array = [True if x%2==0 else False for x in range(0,3)] # will create a boolean array of shape (1,3). For boolean indexing as you saw in 4.py, no of cols of boolean array must be same as number or rows of DataFrame (or ndarray)
print('df[boolean_array] shows boolean slicing a dataFrame\n%s\n' % df[bool_array]) # Will select row 0 and row 2

# dataFrame indexing using a callable
print('df indexing using a callable \n%s\n' % df[lambda x: x['A'] + x['B'] + x['C'] + x['D'] < -1.0])


# indexing columns
# pandas allows a special index for dates. We can create an index using pd.date_range.
dates = pd.date_range('1/1/2000', periods=8) # create dates, 1st to 8th January 2000
dates_df = pd.DataFrame(np.random.randn(8,4), index=dates, columns=list('ABCD'))

# get any column by name
s = dates_df['A']  # note that s will be a series where index is same as DataFrame index
print('get single column dates_df["column_name"] \n%s\n' % s)

# get multiple cols
s = dates_df[['A', 'D']]
print('get random columns dates_df[["column_name1, column_name2"]] \n%s\n' % s)

# get columns by slicing. Slightly trickier, use the dates_df.loc[row_indexer, column_indexer] way.
# with row_indexer = ':'
# remember that dates_df.ix[] method is deprecated and should not be used anymore.
s = dates_df.loc[:, 'A':'B']
print('get adjacent columns dates_df["column_name1:column_name2"] \n%s\n' % s)


# indexing by rows and column both, same as explained above
# dataframe index by both single row and single col will actually give you a cell.
print(df)
cell_value = df.loc['two', 'D'] # must be row indexer, col indexer, cell_value is np.float64
print('df.loc[row_indexer, col_indexer] \n%s %s\n' % (cell_value, cell_value.__class__))

multiple_cells = df.loc[['one','three'], ['A','C']] # multiple_cells is DataFrame object
print('df.iloc[row_indexer, col_indexer] \n%s %s\n' % (multiple_cells, multiple_cells.__class__))


# indexing like attribute access
print('access dataframe like attribute df.B \n%s\n' % df.B)
print('access series like attribute df.B.three \n%s\n' % df.B.three)

s = pd.Series([1,2,3,4], index=list('ABCD'))
print('series s\n%s\n' % s)
# modifying an existing value in series
s.B = 5
print('modify value in series s.B=5 \n%s\n' % s)
# Same for dataframe
df.B.three = -99.999
print('modifying df cell using attribute df.B.three=-99.999 \n%s\n' % df)

# adding element to Dataframe using attribute access fails silently. It creates an attribute of the series and dataframe object, not a value in the series or a column in the dataframe.
df.Z = -100.99
print('adding df cell using attribute df.Z=-99.999 doesnt work \n%s\n' % df.Z) # df.Z is an attribute of the dataframe
# use the dictionary style to add a new column
df['Z'] = list(range(len(df.index))) # df.Z will be 0, 1, 2, 3..
print('df["Z"] = list(rangle(len(df.index))) \n%s\n' % df)

# changing only a few cells in a row
df = DataFrame(np.random.rand(2, 3), index=['one', 'two'], columns=list('ABC'))
print('Changing a few cells example\n%s' % df)
df.iloc[0] = dict(B=10., C=2.56)  # will set rest of the values to NaN
print(df)
di = dict(B=10., C=2.56)  # will set rest of the values to NaN
# get_indexer() takes a list of index labels or col names and returns an ndarray of
# the corresponding numeric indexes. So it doesnt have a side effect of setting other values
# to NaN.
df = DataFrame(np.random.rand(2, 3), index=['one', 'two'], columns=list('ABC'))
print(df)
df.iloc[0, df.columns.get_indexer(di.keys())] = pd.Series(di)
print("df.iloc['one'] = pd.Series() to change one or more cell values in a row \n%s\n" % df)
