# more pandas indexing examples
import numpy as np
import pandas as pd
from pandas import DataFrame

dates = pd.date_range('1/1/2000', periods=8)
df = DataFrame(np.random.randn(8, 4), index=dates, columns=list('ABCD'))
print 'df\n%s\n' % df

s = df['A'] # trivial by now. Get column 'A' which returns a series.
print 's[dates[5]] = %s\n' % s[dates[5]] # get the 6th index. ie 6/1/2000

# cool way of interchanging column names
df[['B', 'A']] = df[['A', 'B']] # cols B is now column A, column A is now column B
print "df[['B', 'A']] = df[['A', 'B']] \n%s\n" % df # cols B is now column A, column A is now column B

# Somehow this doesnt work. I didnt understand the reason
# pandas aligns all AXES when setting Series and DataFrame from .loc, and .iloc.
# This will not modify df because the column alignment is before value assignment.
df.loc[:, ['A', 'B']] = df[['B', 'A']]
# but the workaround is to use .values attribute like below, .values returns an ndarray of the data.
df.loc[:, ['A', 'B']] = df[['B', 'A']].values
print "df.loc[:, ['A', 'B']] = df[['B', 'A']].values \n%s\n" % df
