import os
import math
import time
import random
import sys

# if get_variables/getVariables function exist, only those keys are exported. the other attributes are not exported and ignored silently.
__all__ = ['USER', 'RANDOM_INT', 'CURRENT_TIME', 'AFTERNOON', 'VARIABLES']

USER = os.getlogin()
RANDOM_INT = random.randint(0,100)
CURRENT_TIME = time.asctime()
if (time.localtime()[3]) > 12:
    AFTERNOON = True
else:
    AFTERNOON = False

# Whatever arguments are passed to this variable file, is passed to the get_variable function
VARIABLES = {}
#def get_variables(*args):
#    for i in range(len(args)):
#        radius = float(args[i]) / 2
#        area = math.pi * radius * radius;
#        key = 'AREA' + str(i+1)
#        value = area
#        VARIABLES[key] = value
#    print(VARIABLES)
#    return VARIABLES

#class myvariables(object):
#    SOME_VARIABLE="SOME_VARIABLE_VALUE"
#    pass

