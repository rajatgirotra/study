#!/usr/bin/env python3

## Sets are another type of sequence container in Python. Basically used for the following operations.

## Checking Membership
## Eliminating duplicates
## Union
## Intersection
## Difference
## Symmetrical Difference

## Use curly braces to create a set.

basket =  {'apple', 'banana', 'pomegranate', 'banana', 'oranges', 'apple'}
print(basket)


## Checking for Membership
print('oranges' in basket)
print('nuts' in basket)

##Eliminate duplicates
a = set('abracadabra')
b = set('alacazamn')
print(a)
print(b)

print ('a-b = ', a-b) ## Difference
print ('a Union b = ' , a | b) ## Union
print ('a Intersection b = ' , a & b) ## Intersection
print ('a symmetrical diff b = ', a ^ b) ## Symmetrical Difference

## Sorting elements in a set
print(sorted(basket))
