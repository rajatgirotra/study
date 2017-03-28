
# coding: utf-8

# In[1]:

get_ipython().magic('matplotlib inline')


# In[2]:

import json
from pandas import DataFrame, Series
import pandas as pd
import matplotlib.pyplot as plt


# In[3]:

path = 'usagov_bitly_data2012-03-16-1331923249.txt'
records = [json.loads(line) for line in open(path)]


# In[4]:

frame = DatFrame(records)


# In[5]:

frame = DataFrame(records)


# In[6]:

frame


# In[7]:

clean_tz = frame['tz']


# In[8]:

clean_tz


# In[9]:

clean_tz.fillna('Missing')


# In[10]:

clean_tz = clean_tz.fillna('Missing')


# In[11]:

clean_tz [clean_tz == ''] = 'UNKNOWN'


# In[12]:

tz_counts = clean_tz.value_counts()


# In[13]:

tz_counts[:10]


# In[14]:

tz_counts[:10].plot(kind = 'barh', rot=0)


# In[ ]:



