#!/usr/bin/env python3

# The dir([moduleName]) function is used to display a list of names (variables, functions, modules) which the moduleName argument defines.
# without any parameter, the current module is assumed
# to see a list of built in variables, use dir(builtins)

import sys, fibo, builtins

print(dir(fibo))

print()
print()

print(dir(sys))

print()
print()

print(dir(builtins))
