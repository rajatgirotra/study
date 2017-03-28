#!/usr/bin/env python3

import Modules
# import Modules.one.mone
from Modules.one.mone import mone_func
import sys

print("sys.modules")
print(sys.modules)

print()
print(Modules.mod_init())

print()
# print(Modules.one.mone.i)
#print(Modules.one.mone.mone_func())
print(mone_func())

def foo():
    global my_var
    my_var = 100

if __name__ == "__main__":
    global my_var;
    my_var = 200;
    print(my_var)
    foo()
    print(my_var)
    print()
    print(globals())
