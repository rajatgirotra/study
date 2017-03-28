#!/usr/bin/env python3

## In python , reading and writing is in strings. So every python object has to be converted into a string and back during reading and writing.
## To ease this out, python has a module called pickle to do this conversion for almost every python object.

## Converting a python object to a string representation is called pickling, converting it back is called unpickling.
## this is also the way we achieve persistence, where you can write an object out to a file and read it later by unpickling.

## so lets get started.

import pickle

lst = ['spam', 'eggs', 34, 100, ['nested list']]

with open('persist.bin', 'wb') as f:
   pickle.dump(lst, f)

with open('persist.bin','rb') as f:
   lstBck = pickle.load(f)

print(lstBck)


hashMap = {'ABCD':123, 'XYZW':-987, 'hhkwnw':'rtu'}

with open('persist.bin', 'wb') as f:
   pickle.dump(hashMap, f)

with open('persist.bin','rb') as f:
   hashMapBck = pickle.load(f)

print(hashMapBck)


## So you should remember that whatever classes you write, you should provide support for pickling and unpickling.
