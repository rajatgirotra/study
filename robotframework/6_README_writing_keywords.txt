Writing Keywords
================
Is very trivial. Keywords support positional arguments or variable arguments and named arguments also. Remember that when using named argument syntax, the = operator must be written literally. the argument name and argument value can also be variables defined elsewhere. So even if you have a variable ${ARG_AND_VALUE}="foo=bar", you can't use it in named argument syntax. So you have to be very careful when writing keyword wrappers which wrap a keyword taking named arguments. Example:

| *Keywords*  | *Arguments* |
| Run Program | [Arguments] | @{args}         |
|             | Run Process | some_program.py | @{args} |

| *Test Cases* |
| Run Program  | shell=True |

// will NOT invoke some_program.py shell=True
// it will invokd some_program.py "shell=True" as argument. We'll below how to fix this properly.

Infact you can also pass named arguments which are not in the list of arguments specified by the keyword itself. Just like you can do the same in Python using **kwargs.

Also you can escape named argument syntax by using backslash. example foo=\bar will pass a argument "foo=bar" literally, even if there is an named argument foo in the keyword. Named argument syntax can also be used when importing libraries in the Settings table. Example:

*** Settings ***
Library    Telnet    prompt=$    default_log_level=DEBUG

*** Test Cases ***
Example
    Open connection    10.0.0.42    port=${PORT}    alias=example
    List files    options=-lh
    List files    path=/tmp    options=-l

*** Keywords ***
List files
    [Arguments]    ${path}=.    ${options}=
    Execute command    ls ${options} ${path}



To solve the problem of wrapping keywords which take named arguments, we can use a special syntax. See below: 
1) Run Process is a keyword in the Process library defined as "Run Process command, *arguments, **configuration" ie. it expects a command to run, followed by zero or more arguments and followed by zero or more named arguments. Lets wrap this keyword to always run our script "program.py"

| *Keywords* | *Arguments* |
| Run Program | [Arguments] | @{args}    | &{configuration} |
|             | Run Process | program.py | @{args}          | &{configuration |

| *Test Cases* | *Action*    | *Arguments* |
| Using Kwargs | Run Program | arg1        | arg2       | cwd=/some/path |
|              | Run Program | argument    | shell=True | env=${ENVIRON} |

All keyword settings with explanation
=====================================

See keyword_example.robot next
