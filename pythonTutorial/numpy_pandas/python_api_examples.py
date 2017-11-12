# Please read pandas_missing_data.py first
import pandas as pd
from pandas import DataFrame
import numpy as np

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

# For each animal type and each number of visits, find the mean age. In other words, each row is an animal, each column
# is a number of visits and the values are the mean ages (hint: use a pivot table).
print('pivot_table\n%s' % df.pivot_table(index='animal', columns='visits', values='age', aggfunc='mean'))