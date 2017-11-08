# In pandas, missing data values are also called NA values. The default representation for
# NA values is NaN, but for date/timestamps, the default representation is NaT. You can manually
# assign np.nan to cells in dataframe/series to mark them as missing. Note however, that
# although None==None is True in python, but np.nan != np.nan in python, so never check if a
# value is missing by comparing against np.nan. Always use the isnull(), notnull() etc functions
# for that.

import pandas as pd
from pandas import DataFrame
import numpy as np

frame = DataFrame(np.random.randn(5, 3), index=['a', 'c', 'e', 'f', 'h'],
                  columns=["one", "two", "three"])
# Re-indexing the frame above will introduce NA values.

df = frame.reindex(index=['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'])
print('\nFrame with NA values\n%s' % df)

# Will return a boolean dataframe of same shape with True for all NA Values.
print('pd.isnull(df)\n%s' % pd.isnull(df))
print('pd.isna(df)\n%s' % pd.isna(df))  # isnull and isna are aliases. isna is available in 0.21.0 and later

# Similarly you have notnull() and notna() which are opposite of above

# Add a timestamp column, then manually assign None and np.nan and view the representation

df2 = frame.copy()
df2['Timestamp'] = pd.Timestamp('20120101')
print('\nFrame with timestamp column\n%s' % df2)

# There is a slight difference in assigning None or np.nan to data. We'll discuss in a bit
# df2.loc[['a', 'c', 'h'], ["one", "Timestamp"]] = None
df2.loc[['a', 'c', 'h'], ["one", "Timestamp"]] = np.nan
print('\nFrame with timestamp NA values\n%s' % df2)

# Assigning None or np.nan to numeric or datetime containers always means an NA value
# you can confirm that using the pd.isnull() function
frame = DataFrame(np.random.randn(2, 3))  # frame with numeric data
frame.loc[0, 0] = None
frame.loc[0, 1] = np.nan
print('\nassigning np.nan and None to numeric dataframe\n%s' % frame)
print('\nnumeric container isnull() check\n%s' % pd.isnull(frame))


# Assigning None to object container means assigning NA value. ie. isnull() will be TRUE
# BUT representation will show None
# np.nan will also be NA value and representation will also show NaN.
def get_random_string():
    # Create and return a random string of length 8
    arr = np.random.choice(list('abcdefghijklmnopqrstuvwxyz'), 8)
    return ''.join(arr)

# array of 100 random strings
random_strings = [get_random_string() for _ in range(100)]
random_strings_arr = np.random.choice(random_strings, (3, 4))
frame = DataFrame(random_strings_arr)
print('\nobject(string in this case) container\n%s' % frame)
frame.loc[0, 0] = None
frame.loc[0, 1] = np.nan
print('\nassigning np.nan and None to object container\n%s' % frame)
print('\nobject container isnull() check\n%s' % pd.isnull(frame))

# How missing value is treated. Depends on the API. Some API's like sum() might ignore NA values
# Others might treat NA values as 0. It really depends on the API. So please see API documentation.

# NA Groupby groups are automatically excluded
print('\nframe\n%s' % df)
print('\nNA groupby groups are automatically excluded\n%s' % df.groupby("one").mean())


# Cleanup/Filling up missing data.
# there is a fillna() function used to fill NA values. You can give this function any one of the following
# a scalar value: which is used to fill all NA values in the container
# a method argument like method="bfill" (backfill) or method="ffill/pad" (forward fill) to fill values based on
# values in the next or preceding cell.
# A pandas object that is alignable. Example: a dictionary where keys are column values.
# or a Series with index labels as same as dataframe column values. Let's see examples:
print('\nframe\n%s' % df)
print('\nfillna(scalar)\n%s' % df.fillna(-0.999))

print('\nframe\n%s' % df)
print('\nfillna(method=bfill)\n%s' % df.fillna(method='bfill'))

print('\nframe\n%s' % df)
# df.mean() returns a series where row index labels are dataframe column names
# and we choose only column one and three. which are alignable with dataframe.
print('\nfillna(object)\n%s' % df.fillna(df.mean()[['one', 'three']]))
# So as expected column "two" still has NaN values.

# dropna() - Very trivial, no need to demonstrate, just drop rows (axis=0) or
# cols (axis=1) where a cell has NA value
print('\nframe\n%s' % df)
print('\nframe.dropna(axis=0)\n%s' % df.dropna(axis=0))
print('\nframe.dropna(axis=1)\n%s' % df.dropna(axis='columns'))  # all cols will be dropped.

# Last is the replace API, i am skipping interpolate() API to fill NA values for now.
# The replace API is used to replace an arbitrary value or a range of values in a Series/Dataframe
# We'll now move on to practical problems (ie exercises) and maintain just one more file
# call pandas_api to record important api examples for future reference. So keep updating that
# one.
