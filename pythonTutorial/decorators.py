#!/usr/bin/env python

import string

# Read thru so you understand class's and decorators and then go back to
# function tools.


# How to write a class in python
class Base (object):
    """
    The doc string for the class goes here
    """  # is accessible via Base.__doc__

    # Any members you declare here without prepending "self." will be shared
    # by all instances of the class.
    i = 12345  # can be accessed as Base.i
    tricks = []  # again shared by all instance using Base.tricks

    # C;tor
    def __init__(self, firstname, lastname):
        # Define all member variables here
        self.fname = firstname
        self.lname = lastname

    # a member function
    def foo(self):
        print('foo() ', self.fname, self.lname)

    # Lets declare a classmethod-
    # A class method is a speciall method which gets the class object
    # as its first argument instead of the this pointer (ie the self variable)
    # There are two ways you can do this.
    def cls_method(cls, *args):
        print('Type', type(cls))
        print('Name', cls.__name__)
        print('DocString', cls.__doc__)
    cls_method = classmethod(cls_method)

    # the other way is more compact and preferred.
    @classmethod
    def cls_method2(cls, *args):
        print('Type', type(cls))
        print('Name', cls.__name__)
        print('DocString', cls.__doc__)
    # This way is just synctactic sugar to declare a class method

    # @a
    # void b(*args) means
    # b = a(b)  # so "a" must return a function object

    # Similary
    # @a(args)
    # @b
    # void foo(*fooArgs) means
    # foo = a(arg)(b(foo))  # ie b takes foo and retuns a functio object
    # then a is called with argument arg. "a" must return a function object
    # which takes a function object returned by b.

    # Similarly you have staticmethod also which is also is not given
    # the this pointer. The difference between classmethod and staticmethod
    # is that classmethod is given a class object whereas staticmethod is not
    # given anything by default. Also because python has no concept of function
    # overloading, the class method can be used to manufacture instances of the
    # class which have slightly different function signature. See below
    # where a class method accepts a full name instead of first name and
    # lastname and creates an instance of this class. So you have better
    # program by hiding everything inside the class instead of exposing stuff
    # outside the class
    @classmethod
    def from_full_name(cls, fullName):
        (fname, lname) = string.split(fullName, ' ', 1)
        return Base(fname, lname)

    @staticmethod
    def is_name_valid():  # no class or this pointer
        pass  # can be used to do tasks which are common for the all
              # class instances and also dont require class object

    # Also note that a class can have a __call__ method
    # which makes the class a function object. Just like in C++
    def __call__(self, *args, **kwargs):
        print('Function object called with', args, kwargs)


if __name__ == "__main__":
    oBase = Base('Rajat', 'Girotra')
    oBase2 = Base('Mark', 'Twain')
    oBase3 = Base.from_full_name('Michael Towarek')

    oBase.foo()
    oBase2.foo()
    oBase3.foo()

    print(oBase.i)
    print(Base.i)
    Base.i = 23456
    print(oBase2.i)
    print(Base.i)

    oBase.tricks.append('A')
    oBase2.tricks.append('B')
    Base.tricks.append('C')

    print(Base.tricks)

    # Lets try to call class method using class instance
    oBase.cls_method()  # is allowed but this pointer wont be accessible
    Base.cls_method2()

    # function object behavior
    oFunc = Base('a', 'b')
    oFunc(10, 20, a='aa')
