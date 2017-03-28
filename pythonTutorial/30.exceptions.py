#!/usr/bin/env python3
## Open a file myfile.txt and try to read a line. Convert it to an integer. and check for all exceptions that could occur in this process.

import sys

try:
    with open('myfile.txt', 'r') as f:
        x = f.readline()
        i = int(x.strip())
    input('aaa')
except IOError as err:
    print("I/O Error: {0}".format(err))
except ValueError:
   print("Could not convert data to integer")
except: ## Catch all other exceptions
   print("Unexpected error: ", sys.exc_info()[0])
   raise ## Same as throw 

