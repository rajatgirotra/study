# the main api which does all the heavy weight lifting is the concat api.
import pandas as pd
from pandas import DataFrame

df1 = DataFrame({'A': ['A0', 'A1', 'A2', 'A3'], 'B': ['B0', 'B1', 'B2', 'B3'],
                 'C': ['C0', 'C1', 'C2', 'C3'], 'D': ['D0', 'D1', 'D2', 'D3']},
                index=[0, 1, 2, 3])

df2 = DataFrame({'A': ['A4', 'A5', 'A6', 'A7'], 'B': ['B4', 'B5', 'B6', 'B7'],
                 'C': ['C4', 'C5', 'C6', 'C7'], 'D': ['D4', 'D5', 'D6', 'D7']},
                index=[4, 5, 6, 7])

df3 = DataFrame({'A': ['A8', 'A9', 'A10', 'A11'], 'B': ['B8', 'B9', 'B10', 'B11'],
                 'C': ['C8', 'C9', 'C10', 'C11'], 'D': ['D8', 'D9', 'D10', 'D11']},
                index=[8, 9, 10, 11])

# When concatenating dataframes, we need to give a list of dataframe's to concatenate
# and the axis along which to concatenate. The other important parameters are:
# 1. join: which is used to decide what to do with the other axis. By default its' "outer"
# meaning apply union of other axes. "inner" means apply intersection of other axis.

# 2. join_axes: If you don't want inner or outer, then use the "join_axes" parameter which
# takes a sequence of index labels to include.

# 3. keys: Then you have a "keys" parameter, which is a sequence of keys to use as the
# next level of index labels. So the resultant dataframe will have one more level. These keys are used
# to find out which rows/cols came from which dataframes.

# ignore_index: True/False, means that AFTER the concatenation ignore the original index labels
# and create new index labels from 0 to n-1. Note the original labels are still respected during the merge.

# there are other less important parameters which will discuss long the way.

pd.set_option('display.width', 200)

x = pd.concat([df1, df2, df3])  # default axis=0, ie rows get concatenated.
print('\npd.concat([df1, df2, df3]\n%s' % x)

# instead of giving a sequence of dataframes, you can also give a dictionary. In that case
# the dictionary keys will behave like the keys parameter. Lets see.
di = {'x': df1, 'y': df2, 'z': df3}
frame = pd.concat(di)
print('\npd.concat(dict of frames)\n%s' % frame)
print('\nframe.loc[z]\n%s' % frame.loc['z'])

# Lets concat along cols now.
df4 = DataFrame({'B': ['B2', 'B3', 'B6', 'B7'], 'D': ['D2', 'D3', 'D6', 'D7'],
                 'F': ['F2', 'F3', 'F6', 'F7']},
                index=[2, 3, 6, 7])

frame = pd.concat([df1, df4], axis='columns')  # axis=1, columns will be concatenated
# Note that we will now have duplicated cols B and D buts that ok. Cols can have same name.
print('\npd.concat([df1, df4], axis=1)\n%s' % frame)  # by default you'll see lots of NaN
# as join="outer" by default

frame = pd.concat([df1, df4], axis='columns', join="inner")
print('\npd.concat([df1, df4], axis=1, join=inner)\n%s' % frame)

# using join_axes to choose 2 indexes each from both the frames
frame = pd.concat([df1, df4], axis='columns', join_axes=[pd.Int64Index([0, 1, 6, 7])])
print('\npd.concat([df1, df4], axis=1, join_axes=[0,1,6,7])\n%s' % frame)

# using ignore_index
frame = pd.concat([df1, df4], axis='index', ignore_index=True)
print('\npd.concat([df1, df4], axis=0, ignore_index=True)\n%s' % frame)


# You can also concatenate dataframes and series (ie dataframes when dimensions are not same)
# In these case the series is converted to a column with name same as the series name.
# if the series doesnt have a name, the default col names are given like 0, 1, 2, ...
s = pd.Series(['X1', 'X2', 'X3', 'X4'], name='X')
frame = pd.concat([df1, s], axis=1)  # concat along cols
print('\npd.concat([df1, s], axis=1)\n%s' % frame)

s = pd.Series(['X1', 'X2', 'X3', 'X4'])  # no name
frame = pd.concat([df1, s, s, s], axis=1)  # concat along cols
print('\npd.concat([df1, s, s, s], axis=1)\n%s' % frame)

# ignore_index=True with axis=1
frame = pd.concat([df1, s, s, s], axis=1, ignore_index=True)  # column names will be reset to 0, 1, 2, ...
print('\npd.concat([df1, s, s, s], axis=1, ignore_index=True)\n%s' % frame)

s = pd.Series(['X0', 'X1', 'X2', 'X3'], index=list('ABCD'))
frame = pd.concat([df1, s], axis=0)  # concat along rows, as expected, series was changed
# to dataframe with column name 0
print('\npd.concat([df1, s], axis=0)\n%s' % frame)

# There is an append() api also to concat dataframes, but stick to using concat for now.
# One use of append is to add new rows to end of a dataframe. like in the example above.
# if we use append instead of concat, pandas interchanges the series index and column
# and then does the concat. thereby a new row is added.
s = pd.Series(['X0', 'X1', 'X2', 'X3'], index=list('ABCD'))
frame = df1.append(s, ignore_index=True)  # ignore_index=True is mandatory
print('\ndf1.append(s)\n%s' % frame)

