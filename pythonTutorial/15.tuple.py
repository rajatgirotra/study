#!/usr/bin/env python3

## Tuples are also a collection of heterogenous elements that are enclosed by round brackets.
## They are IMMUTABLE.
## They can be nested.
## They can contain mutable elements
## Pay attention when creating an empty tuple or tuple with just one item
## They can be created with or without braces, although braces are always recommended.
## You can index into them using an index.

t = 12345, 54321, "HelloWorld"
print(t)
print(t[1])

u = t, 1, 2, 3, 4, 5
v = t, (1, 2, 3, 4, 5)

print(u)
print(v)

t1 = ([1, 2, 3],) ## tuple containing a mutable list, note the comma after the list element. Without it python interpreter will not consider it a tuple.
t1[0].append(4) ## You can modify individual items in a tuple., but not change the tuple itself, so t[0] = ("ABC",) is not allowed.
print(t1[0])

t2 = () ## How to create an empty tuple
print (t2)

print(len(t)) ## Size of a tuple. Trivial, just like size of list or string. By the way, list, string, tuple etc are all python sequence types.

x, y, z = t  ## this is called sequence unpacking, basically just the reverse of how t was assigned in the first statement.
print(x)
print(y)
print(z)

## You can also iterate over a tuple like shown below using the enumerate() function. This function returns you the index and the value of the item in the tuple.
## Note the for loop carefully.
## Infact you can use the enumerate() function with any sequence, not just tuples
for i, v in enumerate(t) :
   print('Index:', i, '  ', 'Value:', v)

## Printing a sequence in reveresed order using reversed() function
print(t)

for f in reversed(t):
   print(f)

