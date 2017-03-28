#!/usr/bin/env python3

## the keyword raise is used to raise an exception explicitly. See its use below.

try:
    raise Exception('spam', 'eggs')
except Exception as err: ## creating an instance of the exception.
    print(type(err)) ## Displays the type of the class which is Exception
    print(err.args)
    print(err)
    x, y = err.args
    print('x =',  x)
    print('y =',  y)
