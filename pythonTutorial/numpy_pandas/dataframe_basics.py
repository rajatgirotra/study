# Please read ndarray_indexing_and_slicing and numpy_broadcasting.py first
# Series and dataframe basics
# indexing, slicing is almost the same in series and dataframe as in numpy

from pandas import DataFrame
import pandas as pd
import numpy as np

# Firstly widen the display width
pd.set_option('display.width', 200)

df = DataFrame(np.random.randn(7, 4), index=list('abcdefg'), columns=list('ABCD'))

print('df \n%s' % df)
# Simple indexing to print columns
print('\ndf["B"]\n%s' % df['B'])
print('\ndf.B\n%s' % df.B)

# Slicing will always give rows
print('\ndf[:3]\n%s' % df[:3])

# Indexing using index arrays
print('\ndf.loc[[a,c]] \n%s' % df.loc[["a", "c"]])

# indexing by boolean arrays, note how all -ive values are replaced by NaN
print('\ndf[df>0] \n%s' % df[df > 0])

# printing dataframe index and columns
print('\ndf.index %s, df.columns %s,' % (df.index, df.columns))

# use of iloc: iloc takes numeric indexes
print('\ndf.iloc[[0,3]] will print rows 0 and 3 \n%s' % df.iloc[[0, 3]])

# use of loc: loc takes index labels
print('\ndf.loc[["a", "c"]] will print rows with index a and c \n%s' % df.loc[["a", "c"]])

# use of iloc/loc to print cell values
print('\ndf.iloc[1, 3] will print value in row 1, col 3 \n%s' % df.iloc[1, 3])

# load iris.csv
df = pd.read_csv('iris.csv')
print('\niris.info \n%s' % df.info())

# add sepal_ratio and petal_ratio columns using assign and insert api's
df.insert(2, 'sepal_ratio', df['sepal_length']/df['sepal_width'])
df = df.assign(petal_ratio=lambda x: x['petal_length']/x['petal_width'])
# Note the difference between assign and insert - assign always returns a copy so we use assignment explicitly
print('\ndf with iris ratios \n%s' % df.head())

# move petal ratio column after petal_width ie column index should be 5
df.insert(5, 'petal_ratio', df.pop('petal_ratio'))
print('\ndf with iris ratios after move \n%s' % df.head())

# Lambda indexing ie indexer is a callable
print('\nLambda indexing, iris where sepal + petal ratios > 7\n%s' % df[lambda x: x['sepal_ratio'] + x['petal_ratio'] > 7])