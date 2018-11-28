What are variable files
======================
There are multiple ways in which you can create variables in Robot.

1) On the command line, using -v or -V
-v variable name:value
-V variablefilepath:arg1:arg2 --> variable file path and possible arguments to pass to that file (it is a python file after all).
The arguments are passed as string to the get_variables/getVariables() function defined in the python variable file as you'll see below.
Only string values are supported using -v

2) Using Variable table in your robot files. Example:
*** Variables ***
${VARIABLE}            An example string
${ANOTHER VARIABLE}    This is pretty easy!
${INTEGER}             ${42}
@{STRINGS}             one          two           kolme         four
@{NUMBERS}             ${1}         ${INTEGER}    ${3.14}
&{MAPPING}             one=${1}     two=${2}      three=${3}
@{ANIMALS}             cat          dog
&{FINNISH}             cat=kissa    dog=koira


3) Creating explicit variable files: 
    3.a Variable files are nothing but Python files where variables are declared as module attributes.
    3.b As a convention, always keep variable names in upper case. Variable file also allow a function called "get_variables" or "getVariables" to be implemented which returns a mapping of variable names and value. this approach is very flexible. Variable values can be any object, not necessarily string.


Variables files are searched in the same fashion as Resource files. See the section on resource files for more information. Variables in the Variable table or set by the -v option on the command line always override variables in files.

Accessing Variables
==================
Variables are of multiple types in robot. We have scalar variables, list variables, dictionary variables etc.
Let's assume the following variables are defined. 

VARIABLE = "An example string"
ANOTHER_VARIABLE = "This is pretty easy!"
INTEGER = 42
STRINGS = ["one", "two", "kolme", "four"]
NUMBERS = [1, INTEGER, 3.14]
MAPPING = {"one": 1, "two": 2, "three": 3}

All these variables can be accessed as a scalar variable, Example: ${MAPPING}, ${NUMBERS}, ${INTEGER}
Lists and dictionaries can be accessd as a list variable, example: @{STRINGS}, @{NUMBERS}, @{MAPPING}. Note that accessing a dictionary as a list will only return the keys.
Dictionaries can be accessed as a dictionary variable, exmaple: &{MAPPING}

You can also create variables in python like using LIST__ and DICT__ construct. This makes robot perform extra checking to make sure they are List and Dict types.

from collections import OrderedDict
LIST__ANIMALS = ["cat", "dog"]
DICT__FINNISH = OrderedDict([("cat", "kissa"), ("dog", "koira")])

Cool stuff: Robot automatically creates scalar variables to access values of dictionary keys, like ${FINNISH.cat} will be kissa above.

If your python variable file, has many classes, functions etc; these are also imported as variables. Really you dont want them right..
So there are two ways, create these classes, functions starting with "_". or create an explicit __all__ list attribute with list of all names you want to export.
Also as you read above you can also create a get_variables() function which can take arguments also and return a dictionary where keys are variable names and values are variable values (could be anything, scalar, list, object etc).

You can also create Python classes and all attributes defined in those classes are created as variables. The class name must be the same as module name.

Let's see all these things in action.

NOTE NOTE NOTE
==============
One python variable file can only use one of the three approaches. Either
1) Define module attributes
2) Or define a get_variables/getVariables function
3) or create a class with the same name as the python file and create instance variables there.

