#!/usr/bin/env python3

## Lambda functions
## These are functions which dont have a name, Just like you have anonymous inner classes in Java.
## eg: lambda x : x + n
## Lets just write one such function
## Just like nested functions (functions defined inside other functions), lambda functions can also reference variables from the containing scope: like n is being accessed here in the lambda function.

def make_incrementor(n):
   return lambda x: x + n

f = make_incrementor(42)

print(f(0))
print(f(1))
print(f(2))


## Lets try to write a nested function now.
## A lot of things to learn here.
def outer_function (*keys) :
   ### Documentation.
   """
   Brings together keys and values
   -------------------------------
   This function really accept keys. The inner function accepts values. These are concatenated together and then returned.
   """
   def inner_function(*values) :
      i = 0
      resultList = []
      for key in keys :
         pair = key  + "=" + str(values[i])  ## use function str() to convert to string, values in a tuple can be accessed easily using an index.
         i = i + 1
         resultList.append(pair);
      return resultList;
   return inner_function  ## note that you are retuning the name of the inner function, means return whatever the nested function returns.


foo = outer_function("A", "B", "C", "D")
print(foo(1, 2, 3, 4))

print(outer_function.__doc__)

