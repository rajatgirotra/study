#!/usr/bin/env python3

## Here we will create our first function. You have already seen how to generate fibonacci series. We will write a function to generate fibonacci numbers
## to whatever is passed as argument

## You start with the keyword "def", followed by function name, followed by function arguments, followed by colon.

def fib(n) : ## Generate fibonacci numbers uptil n
   """ Generate fibonacci numbers upto n. """  ## The first statement is an optional string literal, also called as a docstring. It is the function documentation which is read
                                               ## by the interpreter.
   a, b = 0, 1
   while ( a < n ) :
      print(a, end = ', ')
      a, b = b, a + b

   print()


fib(2000)

## When the function is executed, the interpreter create a local symbol table for the function, just like you have stack frame in C/C++. All variables created in the function
## will be in the local symbol table; any variables referenced will first be looked up in the local symbol table, followed by the symbol table of the enclosing function,
## followed by the global symbol table and followed by the table of built-in names. Arguments are also passed by value.

## Also when you define the function, the function name is stored in the current symbol table. It is given a type by the interpreter.
## You can assign a function name to another variable to create an alias for it. Eg:

print(fib) ## Print function information.
f = fib
f(2000)


## By default the function return a value "None" which is a built in name. Printing of the None return value is suppressed by default,
## that's why f(2000) prints nothing. Using print() explicitly will display None as shown below.
print(f(2000))

## Next lets create another version of fibonacci function which does not print anything, but returns a list of fibonacci numbers.

def fib2(n) :
   """ Function that returns a list of fibonacci numbers upto n. """
   result = [] ## Empty list
   a, b = 0, 1
   while ( a < n ) :
      result.append(a)
      a, b = b, a + b

   return result


fibResult = fib2(1000)
print(fibResult)
