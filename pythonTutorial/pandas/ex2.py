#!/usr/bin/env python3

import json
import matplotlib as mpl
import matplotlib.pyplot as plt
from pandas import DataFrame, Series
import pandas as pd
import numpy as np

path='usagov_bitly_data2012-03-16-1331923249.txt'
records = [json.loads(line) for line in open(path)]

print(records[0]['a'])

# The recordss with key 'a' identify browswer name, capabilities and system information
# if we want to split only the first string which identifies browswer capability we can use string.split functions
# string.split(sep=None, maxsplit = 0)
frame = DataFrame(records)
results = Series([x.split()[0] for x in frame.a.dropna()]) # ignore NaN values using dropna()
print(results[:5])

results = results.value_counts()
print(results[:8])

# Now let say you want to find out the number of windows users and non-window users location wise.
# ie time zone wise. So first, we need to find out from key 'a' what OS is being used.
# First filter all records where 'a' is Not null.
cframe = frame[frame.a.notnull()] # will return the frame as is with all rows removed where a is null

## Where use the numpy where function
# np.where(condition[,x,y]), if condition is true return x else return y
# return an ndarray
operating_system = np.where(cframe.a.str.contains('Windows'), 'Windows', 'Non-Windows')
print(operating_system[:10])

#Now for each time zone you want to find out whether the no. of windows and no-window users
# If you thnk about it in your mind, you need to groupby time-zone and operating_system
by_tz_os = cframe.groupby(['tz', operating_system])
print(by_tz_os)  ## Groupby returns a DataFrameGroupBy object

print(by_tz_os.size().unstack().fillna(0))
