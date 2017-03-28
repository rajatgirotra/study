#!/usr/bin/env python3

## Dictionaries in python are equavalent of maps. Jus a key Value Pair. An empty set of braces creates an empty dict {}. 
## See much more below. All this should be trivial for you though now.

tel = {'Rajat':98869763, 'Vidhu':9910076046, 'Raman':25460995, 'Julie':42133533}
print(tel)

## Access based on key
print(tel['Raman'])

## Access based on key which is not available
#print(tel['NoKey']) ## Run time Error (Exception)

## Deleting an entry using del
del tel['Julie']
print(tel)

## Print only the list of keys
print(tel.keys())

## Get the keys as a list and in sorted order
print(list(tel.keys()))

## Check if a key Exists
print('Vidhu' in tel)
print('Julie' in tel)

## You can also use the dict() c'tor like you have the set() c'tor
addressMap = dict([('rajat', 'ed-87'), ('vijay', 'j3-4'), ('vishal','ed-122')])
print(addressMap)

## and finally you can use dict comprehension like you did in set and list.
dictC = { x:x**2 for x in (2, 4,6) }
print(dictC)

## Iterating over a dictionary
for k, v in tel.items() :
   print ('Key:', k, '  ' , 'Value:', v)
