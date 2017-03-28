#!/usr/bin/env python3

## it is always a good idea to create your own set of exception classes.
## You create a new exception class by deriving from the Exceotion standard class.
## You should actually create a base class for your exception and then many derived exception classes
## for each type of exception that might occur in your code.

## First lets create a simple exception class & then later we'll create a set of exception classes.

class MyError(Exception) :  ## Class MyError derives from Exception
    def __init__(self, value) :  ## c'tor, initializes the attribute value
        self.value = value

    def __str__(self) :  ## Function __str__ which returns the value attribute. This function makes it possible to only specify the instance name as an argument to print.
        return repr(self.value)


try :
    raise MyError(2*2)
except MyError as err :
    print('MyError exception with value', err) ## This is achieved by function __str__ as i said above.
    print('MyError exception with value', err.value)

