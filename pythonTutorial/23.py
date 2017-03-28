#!/usr/bin/env python3

## The list of directories to look into to search for modules is:
## 1) The directory from where the main script is invoked
## 2) Followed by whatever is defined the PYTHONPATH environment variable.
## 3) Followed by default paths.

## This is stored in the sys.path variable (which is modifiable list).
## On the command line do "export PYTHONPATH=/cygdrive/abcd"
## and then run this script. Very trivial

import sys

print(sys.path)

sys.path.append("C:\F**kOff")

print(sys.path)
