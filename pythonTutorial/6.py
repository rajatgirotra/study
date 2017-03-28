#!/usr/bin/env python3

## A very simple program to print Fibonacci numbers
## You can initialise variables in the same line as shown below.
a, b = 0, 1

## A simple while loop, followed by :
while (b < 10) :
 ## All while loop statements should be indented. This is pythons way of understanding.
 print(b)
 a, b = b, a + b

## There must be a blank line after the while loop statements so that python knows when the statements end.

## Next you'll see how to use the print command with mutiple arguments.

i = 256 * 256
print ('The value of i is', i, i * 1.2)

## The output shows you how print command automatically introduces a space between multiple arguments. By default print does a line break
## after printing. If you dont want that or want some other character as an end character, use the "end" keyword like below.

print ('The value of i is', i, i * 1.2, end = ',')
##print ('The value of i is', i, i * 1.2)

## See the difference with both these statements above.
