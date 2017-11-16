# Please read pandas_missing_data.py first
import pandas as pd
from pandas import DataFrame
import numpy as np

pd.set_option('display.width', 200)
# Print the version of pandas that has been imported
print(pd.__version__)

# Print out all the version information of the libraries that are required by the pandas library.
print(pd.show_versions())

data = {'animal': ['cat', 'cat', 'snake', 'dog', 'dog', 'cat', 'snake', 'cat', 'dog', 'dog'],
        'age': [2.5, 3, 0.5, np.nan, 5, 2, 4.5, np.nan, 7, 3],
        'visits': [1, 3, 2, 3, 2, 3, 1, 1, 2, 1],
        'priority': ['yes', 'yes', 'no', 'yes', 'no', 'no', 'no', 'yes', 'no', 'no']}

labels = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j']

df = DataFrame(data, index=labels)
# Print multiple columns
print(df[["animal", "age"]])

# Select the data in rows [3, 4, 8] and in columns ['animal', 'age'].
print(df.iloc[[3, 4, 8], df.columns.get_indexer_for(['animal', 'age'])])
print(df.loc[df.index[[3, 4, 8]], ['animal', 'age']])

# Select only the rows where the number of visits is greater than 3.
print(df[df['visits'] > 3])

# Select only the rows where age is NaN.
print(df[df['age'].isnull()])

# Select the rows where the animal is a cat and the age is less than 3.
print(df[(df['animal'] == 'cat') & (df['age'] < 3)])

# between api
# Select the rows where the age is between 2 and 4
print(df[(df['age'] >= 2) & (df['age'] <= 4)])  # or
print(df[df['age'].between(2, 4)])

# Change the age in row 'f' to 1.5.
df.loc['f', 'age'] = 1.5

# Calculate the mean age for each different animal in df
group_by_animal = df.groupby('animal')  # will return an object of DataFrameGroupBy type
# access a column simple using
x = group_by_animal['age']
means = x.mean()
print('mean age by animal \n%s' % means)

# Append a new row 'k' to df with your choice of values for each column.
# Then delete that row to return the original DataFrame.
df.loc['k'] = [3.8, 'dragon', 'no', 1]
print('df with new index k\n%s' % df)
df = df.drop('k', axis='index')
print('df with index k removed\n%s' % df)

# Count the number of each type of animal in df.
# value_counts() gives you a series of count of unique values
print('types of animals \n%s' % df['animal'].value_counts())

# Sort df first by the values in the 'age' in decending order, then by the value in the 'visit' column
# in ascending order.
frame = df.sort_values(by=['age', 'visits'], ascending=[False, True])
print('sort_values() \n%s' % frame)

# The 'priority' column contains the values 'yes' and 'no'. Replace this column with a column of boolean values:
# 'yes' should be True and 'no' should be False
df['priority'] = df['priority'].map({'yes': True, 'no': False})
print('Series.map() to map values in input to output\n%s' % df)

# In the 'animal' column, change the 'snake' entries to 'python'.
# using replace.
df['animal'] = df['animal'].replace('snake', 'python')

# How do you count how many unique rows a DataFrame has (i.e. ignore all rows that are duplicates)?
# use duplicated or drop_duplicates
# df.duplicated() returns a boolean Series. Where entries are duplicated, it return True. So
# if we sum() by column, we get the number of duplicated rows and then we can subtract this
# from the total rows.
# or use drop_duplicated(keep='first') which drops duplicate rows and then just count the rows.
print('\noriginal df\n%s' % df)
print('\nUnique rows in df using df.duplicated()\n%s' % (len(df) - df.duplicated(subset=['animal']).sum()))
print('\nUnique rows in df using df.drop_duplicates()\n%s' % len(df.drop_duplicates(subset=['animal'], keep='first')))

# For each animal type and each number of visits, find the mean age. In other words, each row is an animal, each column
# is a number of visits and the values are the mean ages (hint: use a pivot table).
print('\npivot_table\n%s' % df.pivot_table(index='animal', columns='visits', values='age', aggfunc='mean'))


# Medium hard problems
df = pd.DataFrame({'A': [1, 2, 2, 3, 4, 5, 5, 5, 6, 7, 7]})
print('original df\n%s' % df)
# How do you filter out rows which contain the same integer as the row immediately above?
# use shift to shift values rowwise and then use boolean indexing.
shifted_df = df['A'].shift(1, axis='index')
print('df with rows removed where values matched previous row value\n%s' % df.loc[shifted_df != df['A']])

# Given a DataFrame of numeric values, say
# df = pd.DataFrame(np.random.random(size=(5, 3))) # a 5x3 frame of float values
# how do you subtract the row mean from each element in the row?
df = pd.DataFrame(np.random.random(size=(5, 3)))
print('\noriginal df\n%s' % df)
# Let's first find the row mean
row_means = df.mean(axis=1)  # will be a series with row labels.
print('\nrow_means\n%s' % row_means)
print('\nsubtract the row mean from each element in the row\n%s' % df.sub(row_means, axis=0))

# Suppose you have DataFrame with 10 columns of real numbers, for example:
# df = pd.DataFrame(np.random.random(size=(5, 10)), columns=list('abcdefghij'))
# Which column of numbers has the smallest sum? (Find that column's label.)
df = pd.DataFrame(np.random.random(size=(5, 10)), columns=list('abcdefghij'))
print('\noriginal df\n%s' % df)
# idxmin gives the index of the minimum value in the series.
print('\ncolumn sums\n%s' % df.sum(axis=0))
print('\nindex of min column sum\n%s' % df.sum(axis=0).idxmin())

# You have a DataFrame that consists of 10 columns of floating--point numbers. Suppose that exactly
# 5 entries in each row are NaN values. For each row of the DataFrame, find the column
# which contains the third NaN value. You should return a Series of column labels
df = pd.DataFrame(np.random.random(size=(10, 10)), columns=list('abcdefghij'))
for index, row in df.iteritems():
    nan_indexes = np.random.choice(np.arange(10), size=5, replace=False)
    row[nan_indexes] = np.nan
print('\noriginal df\n%s' % df)
print('third NaN column per row\n%s' % (df.isnull().cumsum(axis=1) == 3).idxmax(axis=1))
# df.isnull() will return a boolean dataframe. cumsum() returns the cumulative sum across
# columns. False is 0, True is 1. So where True is 3 is the index we are interested in.
# Then we get the index using idxmax()

# A DataFrame has a column of groups 'grps' and and column of numbers 'vals'. For example:
df = pd.DataFrame({'grps': list('aaabbcaabcccbbc'),
                   'vals': [12, 345, 3, 1, 45, 14, 4, 52, 54, 23, 235, 21, 57, 3, 87]})
# For each group, find the sum of the three greatest values.
# 2 ways, using df.nlargest(3, 'column_name') or series.nlargest(3)
print('\noriginal df\n%s' % df)
grouped = df.groupby('grps')
print('sum of 3 largest values for each group\n%s' % grouped.apply(lambda x: x.nlargest(3, 'vals').sum()['vals']))
# What we do above is use the apply function on the groupby object. So x will be a DataFrame for every group
# dataframe.nlargest(x, 'column_name') gives the first 'x' largest rows, then we do a sum and use the
# 'vals' column only
print('sum of 3 largest values for each group\n%s' % grouped['vals'].nlargest(3).sum(level=0))
# This is better as we filter the 'vals' columns first. So grouped['vals'] gives a SeriesGroupBy object
# you can apply almost all Series functions to SeriesGroupBy. Here we apply nlargest(), which
# gives a series with MultiIndex, level 0 is the group name, level 1 is the index labels from the
# source dataframe. and we sum by level 0.

# A DataFrame has two integer columns 'A' and 'B'. The values in 'A' are between 1 and 100 (inclusive).
# For each group of 10 consecutive integers in 'A' (i.e. (0, 10], (10, 20], ...), calculate the sum of the
# corresponding values in column 'B'.
# What we will do here is learn the concept of Binning in pandas. Binning means reading
# assigning Categorical data based on quantitative data. Here the quantitative data will be
# the data in column 'A'. We do binning using pd.cut() command.
# 1) the first argument is the array/Series of quantitative data
# 2) the second argument is an array/scalar of how to categorize the data. Example:
# if arg is [0, 10, 20, 30], then categories/bins will be (0, 10], (10, 20], (20, 30]
# 3) the third argument is labels=some_list. This is optional, you can give some labels
# like ['Low', 'Medium', 'High']. If not given the labels will be same as bins in 2nd argument.
# once you bin, its trivial to use groupby and calculate sum. Let's do it.
# Also see what is pd.Categorical type.
# if the first argument to pd.cut is an array, then return type is pd.Categorical
# if the first argument to pd.cut is a Series, then return type is pd.Series with dtype=Categorical.
df = pd.DataFrame({'A': np.arange(1, 101), 'B': np.arange(0, -100, -1)})
df = df.sample(frac=1)  # just shuffle your dataframe
print('\nOriginal df\n%s' % df.head(10))
# Let's bin data first based on column 'A'
df['C'] = pd.cut(df['A'], np.arange(0, 101, 10))
print('\nBinned df\n%s' % df.head(10))
print('\nBinning using pd.cut()\n%s' % df.groupby('C')['B'].sum())


# stack() and unstack() DataFrame or Series.
# stack takes a level parameter (-1 is default). It then converts the columns labels at that
# level to the most inner-most row-labels. So row level increase by one and column levels reduce
# by one. Obviously stack() operation doesn't exist on a series as there is no column.
# unstack() does exactly the opposite. Converts row-labels to column labels.
# Consider a DataFrame containing rows and columns of purely numerical data. Create a list of the
# row-column index locations of the 3 largest values.
df = DataFrame(np.random.randn(4, 3), index=list('abcd'), columns=['one', 'two', 'three'])
print('\nOriginal df\n%s' % df.head(10))
print('\nrow-col location of 3 largest values\n%s' % df.stack().nlargest(3).index.tolist())