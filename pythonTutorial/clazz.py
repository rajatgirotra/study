#!/usr/bin/env python3

import sys

class MyClass:
    """ My first class definition for python practice. """
    x = 12345
    def __init__(self,x, y):
        self.realpart = x
        self.imagpart = y

    def setX(self, value):
        self.x = value


cls = MyClass(3.0,-4.5)
print(cls.x,cls.realpart,cls.imagpart)

cls.setX(0)
print(cls.x,cls.realpart,cls.imagpart)

print()
cls.newVar=2
for i in range(1,10,2):
    cls.newVar = cls.newVar * i;
    print(cls.newVar)

del cls.newVar
        

def foo(a, b, c):
    return "Hello World " + str(int(b+c))

class C:
    f = foo
    def g(self, a, b):
        return self.f(a, b)

c = C()
print(c.g(2,3))

x = 10
y = 'Rajat'

print("c is ", c.__class__)
print("x is", x.__class__)
print("y is", y.__class__)

print(isinstance(x,int))
print(isinstance(x,str))
