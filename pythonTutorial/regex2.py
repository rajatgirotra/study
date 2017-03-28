#!/usr/bin/env python3

# The best way to use regex is to compile your pattern first.
# this returns you a regular expression object. This object can then be
# used in match() and search() calls.
# eg:
# prog = re.compile(pattern, flags = 0), where multiple flags can be added using OR (| operator)
# result = prog.match(string)
# flags can be re.A, re.S, re.I, re.L, re.M, re.V for all the (?a), (?s), (?i) etc options you had seen before.

import re

print('regex.search()')

pattern = 'o'
prog = re.compile(pattern)
result = prog.search('dog')
print(result) ## Prints some object details meaning search was succesull, otherwise will return None.
print(result.group(0)) # prints o


pattern = 'd'
prog = re.compile(pattern)
result = prog.search('dog', 1, 3)
print(result) ## Prints None

pattern = '^o'
prog = re.compile(pattern)
result = prog.search('dog', 1, 3)
print(result) ## Prints None, note here that ^ matches the real string 'dog', which does not start with o.
              ## It does not start at the index which you specify in the search() function.

# A similar function called "match()" also exists.

print()
print()
print('regex.match()')
pattern = 'o'
prog = re.compile(pattern)
result = prog.match('dog') 
print(result) ## No match. match() will always match at the beginning of the string.

pattern = 'd'
prog = re.compile(pattern)
result = prog.match('dog', 1, 3)
print(result) ## Prints None

pattern = 'o'
prog = re.compile(pattern)
result = prog.match('dog', 1, 3)
print(result) ## Matches.
            
# The important difference between search and match is that search will match anywhere in the string
# whereas match will only match at the beginning of the string.
# To restrict search() to only match at the beginning, use the ^ operator in the pattern.
# But remember, for multi-line strings, match() will still match at the beginning ONLY, whereas
# search() with ^ will match at the beginning and at the beginning of every new line.


# Some important attributes of the Compiled Regular expression object
# the following is a re pattern to match an email address optionally surrounded by less than/greater than operators
prog = re.compile('(?a)(<)?(\w+@\w+(?:\.\w+)+)(?(1)>|$)', re.I)
#Attributes
print()
print()
print('Compiled RE object attributes')
print('Pattern String: ' + prog.pattern)
print('Count of pattern subgroups:', prog.groups)
print('Mapping of groupNames(if any) to numbers:', prog.groupindex)
print('Pattern Flags:', prog.flags)


# You have already seen search() and match(). Lets see some more functions in the compiled RE object class.
# split(string, maxsplit=0)
