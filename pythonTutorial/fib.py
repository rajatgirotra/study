#!/usr/bin/env python3

def fib(x):
    """ Print all fibonacci numbers less than x. """
    a, b = 0, 1
    while(a < x):
        print(a, end=', ')
        a, b = b, a+b


def fib2(x):
    """ returns a list of fibonacci numbers less than x. """
    a, b = 0, 1
    l = []
    while(a < x):
        l.append(a)
        a, b = b, a+b
    return l

if (__name__ == "__main__"):
    fib(100)

    print()
    f = fib
    f(200)

    print()
    print(fib2(300))
