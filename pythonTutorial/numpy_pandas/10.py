import numpy as np
import pandas as pd
from pandas import DataFrame

# create a random DataFrame
df = DataFrame(np.random.randn(50, 4), columns=list('ABCD'))
print df

# choose a column
print 'Column A\n %s' % df['A'].head()

# adding a new column
df['E'] = df['A'] + df['B']
df['F'] = df['E'] > 0
print 'df after adding E and F columns \n%s' % df.head()

# deleting a column
del df['C']
print 'df after deleting column C \n%s' % df.head()

# get and delete ie. pop
colF = df.pop('F')
print 'column F \n%s' % colF.head()
print 'df after popping column F \n%s' % df.head()

# assigning a scalar will apply to all columns
df['scalar'] = 5.6
print 'df after creating a column with scalar  value \n%s' % df.head()

# adding a new column (Series), but with a different index. Pandas aligns indexes automatically
s = df['A'][:5]
print 'series df["A"][:5] \n%s' % s
df['new_col_diff_index'] = s
print 'df after adding a new series with different index\n%s' % df.head(10)
del df['new_col_diff_index']

# you can also add a column at a particular position using DataFrame.insert()
df.insert(0, 'NewColAtIndex0', df['A']*df['B'])
print 'df.insert() - insert new column at any index\n%s' % df.head(10)
del df['NewColAtIndex0']

# a good way to introduce new columns is to use the DataFrame.assign(**kwargs) method. This method returns a dataframe object, so it can be chained to add multiple columns. The argument is a dictionary where the key is the column heading and the value is a Series or numpy array or a function taking one argument which is the dataframe object itself. This function is used to add columns where values depends on the existing columns. remember that assign always returns a copy of the dataframe, the original df is untouched.
df = df.assign(G=lambda x: x['A']+x['B'], H=True).assign(I=lambda x: x['A']-x['B'])
print 'df.assign().assign() \n%s\n' % df.head()

# DataFrame query() function takes a string expression and returns the data frame with the rows matching the expression. The expression can use column names as i can see. More on this later.
print 'df.query() \n%s' % df.query('A>0').head()

