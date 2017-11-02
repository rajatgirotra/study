# pandas provides a SQL type join operation for joining two dataframes. Let's look into the
# api and a few examples

# you can use either the join() api in pandas or the join() instance method on the dataframe.
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

# pandas has a merge() method which is also available as an instance method on the dataframe object
# the join() method internally used merge() for the one-to-one (also the default join method) and for the
# column to index join. So use join() as it saves you some typing.

# lets see some examples now. Remember to set indicator=True always.
