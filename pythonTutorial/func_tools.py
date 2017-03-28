#!/usr/bin/env python

import os
import functools
import locale

# functools module provide some functions to that help in python 2 to 3
# migration and some higher level operations.

# Function 1: A lot of functions in python 2 support a comparison function
# as argument. A comparison function is a function which takes 2 objects of
# the same type and return -1, 0 or 1 based on comparison. This was removed
# from python 3 and these functions now accept a key (a function with a single
# argument and a single return value, (int, double, string etc)). This key
# function is now used instead of the the comparison function"

functools.cmp_to_key(locale.strcoll)  # Remember you are not passing arguments
# to strcoll, just passing the function name.
# strcoll takes two string and compares them according to the locale setting.
# cmp_to_key basically will  convert this function into a key function.

# Function 2 - functools provides a function "total_ordering" which takes a
# class name as argument. Very similar to boost operators.
# where you define the < and = operators and all others are implicitly defined.
# lets see
@functools.total_ordering
class Student:
    # ctor
    def __init__(self, fname, lname, marks):
        self.firstname = fname
        self.lastname = lname
        self.marks = marks

    def __lt__(self, other):
        # Lets also learn about tuple & list comparisons.
        # Tuples & list can be compared. Python compares corresponding elements
        # of the sequence. They compare equal if every element is equal and the
        # sequence types are also equal. If the first sequence is shorter, it
        # is assumed smaller when ordering. Otherwise, the result is the result
        # of comparison where two elements are unequal. So here we compare
        # tuples
        return ((self.lastname, self.firstname) <
                (other.lastname, other.firstname))

    def __eq__(self, other):
        return ((self.lastname, self.firstname) ==
                (other.lastname, other.firstname))

    def __str__(self):
        return self.firstname + ' ' + self.lastname

    def __repr__(self):
        return self.firstname + ' ' + self.lastname

# function 3. functools.reduce() -
# The reduce function takes a function (which accepts two arguments), followed
# by a sequence and an initiliazer. The function passed will be called with
# two items from the sequence repeatedly and it can apply any operation on them
# and return a value. So the whole list is reduced to a single value.
# Very trivial.
seq = [1, 2, 3, 4, 5]
value = functools.reduce(lambda x, y: x + y, seq, 100)
# So initial value is 100. The function calls will be
# (100, 1), (101, 2), (103, 3), (106, 4), (110, 5)
print(value)

# function 4 - partial.
# Ok, Let say you have some function foo(args, keywordargs)
# you can bind some arguments to this function foo using functools.partial
# Which returns you a partial object (similarly like std::bind), which returns
# like a function object. So partial here is a function object
# But when you actuall call this partial object, you can specify some more
# args and keyword args. These new args are appended to the older args
# Already binded, and keywords override if they have the same key, otherwise
# they are appended. Lets see it in action. partial is called a function
# object in python; ie they are callable, weak-referencable, and can have
# attributes. See the simple function below and then go to main.


def foo(*args, **keyargs):
    """
    I am function foo
    """
    print ('Args', args)
    print ('Keyargs', keyargs)
    

# function 5 - update_wrapper - Read about this if you know/remember
# what decorators are. Otherwise read about decorators in decorators.py first.
# and then return here. Actually go to wrapper.py as it is slightly complex


if __name__ == "__main__":
    s1 = Student('Rajat', 'Girotra', 178)
    s2 = Student('Michael', 'Towarek', 112)
    l = [s1, s2]

    print (sorted(l))

    # create a partial object
    partialObj = functools.partial(foo, 'a', 'b', c=3, d=4)
    print('partialObj.func ', partialObj.func)
    print('partialObj.args ', partialObj.args)
    print('partialObj.keywords ', partialObj.keywords)
    partialObj()
    partialObj(23, 26, acid='h2so4')
