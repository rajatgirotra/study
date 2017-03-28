#!/usr/bin/env python3

## List comprehensions : a short way to create lists. More like the set notation X = {x : x is even and x > 0 and x < 10}

squares = [ x for x in range(10) ]   ## "for" is the important keyword here.
print(squares)

squares = [ x**2 for x in range(12)]
print(squares)

squares = [(x, y) for x in [1, 2, 3] for y in [2, 3, 4] if x != y ]
print(squares)

vec = [-6, -4, -2, 0, 2, 4, 6, 8]
squares = [x for x in vec]
print(squares)

squares = [x for x in vec if x > 0]
print(squares)


squares = [abs(x) for x in vec]
print(squares)


## Wasn't that difficult was it. OK you know that a list can be nested inside another list
## So we can have list comprehensions that are nested.
## Consider the following matrix

matrix = [
   [ 1, 2, 3, 4 ],
   [ 5, 6, 7, 8 ],
   [ 9, 10, 11, 12]
 ]

## Can u think about c'ting  a matrix using list comprehension which is a transpose of this matrix??
## think this way..
## Each element of the above list is what?? Its a list. So now the list comprehension should be

## transposeMatrix = [ [something that represents a list] for i in range(4)] ## because the transpose will have 4 rows.

## Now how can you populate the [something that represents a list]
transposeMatrix = [ [row[x] for row in matrix] for x in range(4)]
print(transposeMatrix)

## but just to let you know we already have a function to get the transpose, using the * operator and zip() function.
transpose = list(zip(*matrix))
print(transpose)
