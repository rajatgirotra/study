#!/usr/bin/env python3

## Sample of the Std library functions.

import os

print(os.getcwd()) ## get current working directory.

print(os.chdir('/cygdrive/c/tools')) ## Change directory, returns None
print(os.getcwd()) ## get current working directory.

print(os.system('mkdir newPythonDir')) ## Issue a system call using system() function, returns 0 on success and a positive integer to signal an error. Run this twice
                                       ## the second time, you'll see an error.


print(dir(os)) ## print all the variables available in the os module.

help(os) ## Starts out a help manual page

import shutil  ## A python module for high level file operations. Majorly for copying, moving, removal of files or list of files.

import glob ## Another python module. This is used to find all the pathnames which match a given regular expression. All of the unix shell wildcards like *, ?, [], are respected.
     ## Just two functions in this module. glob() and iglob()

glob.glob('./[0-9].*') ## returns 1.gif, 2.txt

glob.glob('*.gif') ## returns 1.gif, card.gif

glob.glob('?.gif') ## returns 1.gif, note files starting with . are not listed in this.

##iglob(pathname) - Same as glob(pathname), but returns an iterator instead of a tuple of pathnams.

import sys ## For reading command line aruments mostly

print(sys.argv)

## Also you have std.stdout, std.stdin, std.stderr used to redirect error messages to make them visible even when stdout has been redirected.

import re ## For string pattern matching.

import math ## For maths.

from urllib.request import urlopen ## For internet
import smtplib ## For sending email.

## So you have seen
# os
# shutil
# glob
# math
# re
# urlopen
# smtplib
# sys
# date (from datetime)
# zlib ## For data compression

