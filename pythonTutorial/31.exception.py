#!/usr/bin/env python3

## there are two learnings here:
## Notice the use of else block with try..except.

## second, we create an instance of an exception that is raised (err). This has a variable args which is a tuple of the actual error detail.
## Normally all exceptions have an __str__ variable to print the err details as such, so we can just say print(err), or we could say print(err.args)
## which displays the tuple containing the error details. Minor difference between the two, You can see that for urself.

import sys

for arg in sys.argv[1:] :
    try:
        f = open(arg, 'r')
    except IOError as err :
        print('I/O Error:', err.args)
    ## Notice the else clause with try..except. It is used to make sure these statements are executed when an exception is NOT THROWN. So you ask what is the problem
    ## in putting these inside the try block only. This is done to avoid accidently handling exceptions.
    else:
        print(arg, 'has', len(f.readlines()), 'lines')
        f.close()
