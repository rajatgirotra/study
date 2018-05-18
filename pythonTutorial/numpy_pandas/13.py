# pandas slicing
import numpy as np
import pandas as pd
from pandas import DataFrame

period=10
dates = pd.date_range('1/1/2000', periods=period)
s = pd.Series(np.random.randn(period,), index=dates)

# simple slicing
print('s[:5] \n%s\n' % s[:5]) # print index 0 to index 4

# slicing using ::
print('s[::3] \n%s\n' % s[::3])  # print every 3rd row

# print in reverse order
print('s[::-1] \n%s\n' % s[::-1])

# copy series
s1 = s.copy()
# modifying
s1[:5] = 999.999
print('s1[:5] = 999.999 \n%s\n' % s1[:5])

s1[::3] = 3.33
print('s1[::3] \n%s\n' % s1[::3])  # print every 3rd row

df = DataFrame(np.random.randn(2,3), index=range(2), columns=list('ABC'))
print('df[::-1] \n%s\n' % df)

df_dates = DataFrame(np.random.randn(7,3), index=pd.date_range('1/1/2000', periods=7), columns=list('ABC'))
try:
    df_dates.loc[2:3]  # error ofcourse, because labels are dates, not ints and ints are not convertible to dates
except Exception as e:
    print('exception %s' % e)
print("df_dates.loc['20000101':'20000103'] \n%s\n" % df_dates.loc['20000101':'20000103'])
print("df_dates.loc['20000101':'20000131'] \n%s\n" % df_dates.loc['20000101':'20000131'])

print("df_dates.iloc[2:4] \n%s\n" % df_dates.iloc[2:4])
