#!/usr/bin/env python3

# Start ipython notebook "ipython notebook"
# Then you can run commands here one by one there are understand.

import json
from collections import defaultdict
from collections import Counter
from pandas import DataFrame, Series
import pandas as pd
import matplotlib.pyplot as plt

# the file usagov_bitly_data2012-03-16-1331923249.txt' contains
# data in json format
# let read it (deserealize it) with json

path = 'usagov_bitly_data2012-03-16-1331923249.txt'
records = [json.loads(line) for line in open(path)]

# each record in records is a dict()
print(len(records))

print(records[0])

# Imagine this data set in an excel spread sheet where the colunmns are the Keys
# and each row is a value row. Cells can be empty if there is no value for a key in that particular row/record.

# Lets find out the most frequently occurrring time-zone in records ie key 'tz'
# We need some way to group all time zones. Let extract them to a list first
time_zones = [rec['tz'] for rec in records if 'tz' in rec]
print(time_zones)
print(len(time_zones))

#Now put them in a dictionary where the value is the number of times each time_zone is occurring.
def count_time_zones(sequence):
    counts = defaultdict(int)
    for tz in sequence:
        counts[tz] += 1
    return counts

tzDict = count_time_zones(time_zones)
print(tzDict['America/New_York'])

# Now we will need to interchange the key and value
def top_counts(counts):
    counts = {}
    counts = [(count, tz) for tz, count in tzDict.items()]
    counts.sort()
    return counts

tzByCount = top_counts(tzDict)
print(tzByCount[-10:]) # will print top 10

# Look at the Counter class in the collections library.
# This class cab be basically used whenever you have some key
# and the value type is integer. Then using this class
# you can do all sorts of arithmetic on those types. Very iinteresting
# Also it provides a most_common([n]) function to return the top counts.
tzByCount = Counter(tzDict)

print(tzByCount.most_common(10))

# We'll now see how easy it is to do all this with Pandas
# The basic data set in pandas is DataFrame and Series
# Think about DAtaFrame as exactly a data set in excel as explained above.
# and a Series is a particular column. All data belonging to a particluar key
frame = DataFrame(records)
tz_counts = frame['tz'].value_counts()
# frame['tz'] gives us the Series for time zones. and the value_counts method
# gives us what we are looking for. A sub-total by value.
# Print top ten
print(tz_counts[0:10])

# now we want to plot the above 10 time_zones in matplotlib
# but for that we need to assign some dummy value to the missing time_zone
# which has value 521
# Where time zone is missing, we set as Missing
# where time zone is available but an empty text, we set UNKNOWN
clean_tz = frame['tz'].fillna('Missing')
clean_tz[clean_tz == ''] = 'UNKNOWN'  # see the elegent syntax
tz_counts = clean_tz.value_counts()
print(tz_counts[0:10])  # tz_counts, clean_tz and tz_counts[:10]
# are all pandas.core.series.Series

# Now lets plot a horizontal bar plot
horPlot = tz_counts[0:10].plot(kind='barh', rot=0)


#Before we go ahead, lets take a disgress and study about pandas Series type.
# Please series.py next. All of the series here is saved also in 

