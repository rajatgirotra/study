$ cat arg.py
#!/usr/bin/env python3

import argparse

# step 1: create an object of ArgumentParser.
parser = argparse.ArgumentParser(description='Process some integers')

# Add arguments to the argument parser.
parser.add_argument('integers', metavar='N', type=int, nargs='+', help='an integer for the accumulator')
parser.add_argument('--sum', dest='accumulate', action='store_const',const=sum, default=max, help=\
                    'sum the integers (default: find the max)')

# parse sys.argv. This returns you a namespace object
# by default parses sys.argv. It can also take a string parameter in which case it will treat that string
# as sys.argv
args = parser.parse_args()

# use the arguments
print (args.integers)
print(args.accumulate(args.integers))

# How it works.
# First you create an instance of ArgumentParser. You can pass it variety of arguments like
# prog= "Name of program". Default is sys.arrgv[0]
# usage="Usage". Default is derived automatically based on arguments you add.
# description="Custom text that is shown before printing usage"
# epilog = "Custom text that is shown after printing usage"
# prefix_chars = the set of characters that prefix optional arguments. Default is '-'.
# so all arguments prefixed with - will be optional like --sum above.
# add_help = True/False. Default is true, meaning add parameter (-h|--help) automatically
# and some others. Also the program name is accessible in the description using %(prog)s format sepcifier.

# next you add parameters using add_argument()
# then you parse sys.argv[] using parse_args(). This returns you an object which has the same attributes(member
# variables) as the argument names.

# Then you can use it in whichever way we want. In the above example, the attribute names are
# integers and accumulate

