#!/usr/bin/env python3

import sys
import os

# os.error is an alias for the builtin OSError exception.

print(os.name) # prints posix or nt or ce or java
print (sys.platform) # provides more granularity than os.name

# in Posix, filenames, commandline arguments and env variables are all represented as strings
# However, in some OS's you need to convert between string and bytes for passing them to OperatingSystem
# the encoding used will be sys.getfilesystemencoding()
print(sys.getfilesystemencoding())

#print environment
print (os.environ)
print()
if ('JAVA_HOME' in os.environ):
    print(os.environ['JAVA_HOME'])

#Modify environment
os.environ['JAVA_HOME']='/puma/prod/jdk1.7.0_20'
print()
if ('JAVA_HOME' in os.environ):
    print(os.environ['JAVA_HOME'])

del os.environ['JAVA_HOME']
print()
if ('JAVA_HOME' in os.environ):
    print(os.environ['JAVA_HOME'])
else:
    print('JAVA_HOME is not set')

#change directory
print(os.getcwd())

# Open file using fdopen
fd = open('writeFile.txt', mode = 'w')
fo = os.fdopen(fd, mode='w')
x = fo.write("This is line 1\n")
fo.close()
