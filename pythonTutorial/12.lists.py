#!/usr/bin/env python3

## Functions of list class.

## append(x) - append an element to the list
## extend(L) - append list L to the end of this list
## sort() - sort it
## insert(indx, x) - insert x at index indx, 
## reverse() - reverse the list
## remove(x) - remove the first occurrence of item x
## pop([i]) - With no argument, pop the last element. With given index indx, pop element at that index.
## count(x) - the no. of times x occurs in the list
## index(x) - Return the index of x in the list
## len(list) - no. of items in the list
## del list[index] - delete the item at the given index

## Now using the above use list to act as stack and Queues

## Stack first, LIFO


engList = ['spam', 'eggs']
engList.append('cashew')
engList.append('strawberry')

print(engList.pop())
print(engList.pop())


## Queue FIFO

engList.append('groundnuts')
engList.append('hazelnuts')

print(engList.pop(0))
print(engList.pop(0))

## the zip() function allows you to iterate over two sequences at the same time.
## See below. Also note a new way to format strings in the output.

listA = ['name', 'activity', 'color']
listB = ['Rajat', 'Sports', 'Black']

for v1, v2 in zip(listA, listB) :
   print(v1, v2)
   print('What is your {0}? It is {1}.'.format(v1, v2))

for v0 in zip(listA, listB) : ## This time though v0 will be a tuple of two values.
   print(v0)

