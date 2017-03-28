#!/usr/bin/env python3

## Lets now see classes and objects in action
## I'll try to expain things along the way.

class MyClass :
    """A simple example class""" ## Documentation for the class. Accessible using the __doc__ attribute name of the class. You'll see this in a bit.

    x = 12345 ## Defining an attribute of a class.

    def f(self): ## Defining an attribute function of the class. This is called a function object. The argument self is a reference to the class object, just like you have this in C++.
        return "Hello World"

    def __init__(self, realpart, imagpart) : ## Defining the c'tor for the class.
        self.r = realpart
        self.i = imagpart

## defining an instance of this class.
myCls = MyClass(3.0, -4.5)  ## pass two arguments.. the this argument is passed implicitly.
print(myCls.x, myCls.r, myCls.i) ## Note that x is defined explictly in the class, whereas r and i are defined inside the c'tor.

myCls.counter = 1 ## See we can declare an attribute afterwards also. The moment you define it, it springs into action.
while (myCls.counter < 16) :
    myCls.counter = myCls.counter * 2;
    print(myCls.counter)

del myCls.counter  ## delete it as we are done, so it does not even leave a trace about its existence.


## Calling a function. First bind it to a instance.
print(myCls.f())  ## myCls.f here is called a method object.

## A method object can be aliased and called later
myClsF = myCls.f
print(myClsF())

##Just like member variables, you can define member functions also in a very strange way.

def foo(self, x, y) :  ## An ordinary function. You'll see how easily we can make it a member of our class.
    print(x, y)

class C:
    f = foo
    def g(self):
        self.f(2, 3)

c = C()
c.g()

print('Type of class attribute myCls is', myCls.__class__) ## Every object has this attribute.
x = 5
y = 'Rajat'
print(x.__class__)
print(isinstance(x,int))
print(isinstance(y,int))

print(isinstance(myCls, MyClass)) ## isinstance(x, y) returns true if x is an instance of y or any subclass of y.

## Similarly we have issubclass(x, y)
