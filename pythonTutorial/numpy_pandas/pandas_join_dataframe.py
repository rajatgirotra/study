# pandas provides a SQL type join operation for joining two dataframes using the merge() API. Let's look into the
# api and a few examples

# the merge() api arguments are:
# Arguments:
# left = the left dataframe
# right = the right dataframe
# how = "inner" by default, ie. get intersection of two dataframes. Other valid values are
#       "outer" : meaning full outer join
#       "left": meaning left outer join
#       "right": meaning right outer join
# on = keys keys on which join is to be done. If not specified and the left_index and right_index
#      arguments are also False, pandas will use the intersection of the columns as the keys
#      on which join will be made
# left_index: If True, use the left index (row labels) from the left dataFrame as its join keys
# right_index: similar as above. We'll see example
# left_on = keys
# right_on = keys. Used in cases where column names are different. If column names are same, then use
#            "on" argument
# sort = True by default
# suffixes = (_x, _y). If the dataframes have same column names, use these suffixes to distinguish them
# indicator=True/False. Good to make it True. When True, a new column name "_merge" will be added
#           with values "left_only", "right_only" or "both" to indicate where the values in that row have
#           come
# validate: will see later. Basically used to validate that the dataframe values are as expected after the join

# There are three types of merging we can do which we will see in detail. Its very important to understand this.
# one to one join: ie. joining dataframes based on their indexes.
# many to one join: ie joining an index to one or more columns in a dataframe
# many to many join: ie joining columns on columns

# pandas has a join() method which is available as an instance method on the dataframe object
# the join() method internally used merge() for the one-to-one (or index-to-index join) and for the
# column to index join. So use join() as it saves you some typing. But here we will continue to use
# merge so we can better understand that API.

# lets see some examples now. Remember to set indicator=True always.

# Joining on index. When joining on index, DataFrame.join() in convenient, but we'll use
# the pd.merge() so we pass arguments explicitly to understand what we are doing

from pandas import DataFrame
import pandas as pd

df1 = DataFrame({'A': ['A0', 'A1', 'A2'], 'B': ['B0', 'B1', 'B2']},
                index=['K0', 'K1', 'K2'])

df2 = DataFrame({'C': ['C0', 'C2', 'C3'], 'D': ['D0', 'D2', 'D3']},
                index=['K0', 'K2', 'K3'])

print('\ndataframe df1\n%s' % df1)
print('\ndataframe df2\n%s' % df2)

# join on index. Very trivial
# If left_index=True, then right_index should also be True or right_on should be specified,
# otherwise merge() won't know the keys to use on the right dataframe.
frame = pd.merge(df1, df2, how='outer', left_index=True, right_index=True, indicator=True)
print('\ndataframe merge on index, how=outer\n%s' % frame)

frame = pd.merge(df1, df2, how='inner', left_index=True, right_index=True, indicator=True)
print('\ndataframe merge on index, how=inner\n%s' % frame)

frame = pd.merge(df1, df2, how='left', left_index=True, right_index=True, indicator=True)
print('\ndataframe merge on index, how=left\n%s' % frame)

frame = pd.merge(df1, df2, how='right', left_index=True, right_index=True, indicator=True)
print('\ndataframe merge on index, how=right\n%s' % frame)

# So index-to-index join is trivial. column-to-index join is used when the index in one dataframe
# is a column in the other dataframe. Let's see.

df1 = DataFrame({'A': ['A0', 'A1', 'A2', 'A3'], 'B': ['B0', 'B1', 'B2', 'B3'],
                'key': ['K0', 'K1', 'K0', 'K1']})

df2 = DataFrame({'C': ['C0', 'C1'], 'D': ['D0', 'D1']},
                index=['K0', 'K1'])
print('\ndataframe df1\n%s' % df1)
print('\ndataframe df2\n%s' % df2)

frame = pd.merge(df1, df2, how='outer', left_on='key', right_index=True, indicator=True)
print('\ndataframe merge on col-and-index, how=outer\n%s' % frame)
frame = pd.merge(df1, df2, how='right', left_on='key', right_index=True, indicator=True)
print('\ndataframe merge on col-and-index, how=right\n%s' % frame)

# merging on multiple indexes (hierarchical index)
df1 = DataFrame({'A': ['A0', 'A1', 'A2', 'A3'], 'B': ['B0', 'B1', 'B2', 'B3'],
                'key1': ['K0', 'K0', 'K1', 'K2'], 'key2': ['K0', 'K1', 'K0', 'K1']})
# if you want to use left_on=['key1', 'key2'] and right_index=True, then the right data
# should have hierarchical index. Lets create that first
index = pd.MultiIndex.from_tuples([('K0', 'K0'), ('K1', 'K0'), ('K2', 'K0'), ('K2', 'K1')])

df2 = DataFrame({'C': ['C0', 'C1', 'C2', 'C3'], 'D': ['D0', 'D1', 'D2', 'D3']},
                index=index)
print('\ndataframe df1\n%s' % df1)
print('\ndataframe df2\n%s' % df2)
frame = pd.merge(df1, df2, how='outer', left_on=['key1', 'key2'], right_index=True, indicator=True)
print('\ndataframe merge on cols-and-index(hierarchical), how=outer\n%s' % frame)

# Merging single index dataframe with multiindex dataframe
df1 = DataFrame({'A': ['A0', 'A1', 'A2'], 'B': ['B0', 'B1', 'B2']},
                index=pd.Index(['K0', 'K1', 'K2'], name='key'))

index = pd.MultiIndex.from_tuples([('K0', 'Y0'), ('K1', 'Y1'),
                                   ('K2', 'Y2'), ('K2', 'Y3')], names=['key', 'Y'])
df2 = DataFrame({'C': ['C0', 'C1', 'C2', 'C3'], 'D': ['D0', 'D1', 'D2', 'D3']},
                index=index)
print('\ndataframe df1\n%s' % df1)
print('\ndataframe df2\n%s' % df2)

# when you use the join API like
frame = df1.join(df2, how='outer')  # by default join joins on keys. But here it know that dataframe have
# one and 2 indexes. So it automatically matches the index names and merge/joins on the bases
# of index names
print('\ndataframe join single index with multiindex, how=outer\n%s' % frame)

# if you want to do the same thing as above using pd.merge(), you'll have to use reset_index()
# reset_index() converts index (row labels) to columns with index name given or level_0, level_1
# and so on.
df1.reset_index(inplace=True)
df2.reset_index(inplace=True)
print('\ndataframe df1.reset_index()\n%s' % df1)
print('\ndataframe df2.reset_index()\n%s' % df2)
# Once you have reset, its trivial to merge, but then we have to set_index() again after the
# merge
frame = pd.merge(df1, df2, how='outer', on='key', indicator=True)
frame.set_index(['key', 'Y'], inplace=True)
print('\ndataframe merge on single index with multi-index, how=outer\n%s' % frame)

# Amazing stuff
