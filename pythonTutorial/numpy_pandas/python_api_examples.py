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