| *Settings* | *Value*         |
| Library    | OperatingSystem |
| Library    | BuiltIn         |
| Variables  | myvariables.py  | 2 |

| *Variables*    | *Value*     | *Value* |
| ${SCALAR}      | Hello World |
| ${INTEGER}     | ${42}       |
| @{STRING_LIST} | one         | two | three |
| @{NUMBERS}     | 1           | 2   | 3     |
| &{MAPPINGS}    | cat=meow    | dog=bark    |

| *Test Cases* | *Action* | *Argument* | *Argument* |
| Sample Test  | Log | \${SCALAR}=${SCALAR} | level=WARN
|              | Log | \${INTEGER}=${INTEGER} |
|              | Log | \${STRING_LIST}=${STRING_LIST} |
|              | Log | \@{STRING_LIST}=@{STRING_LIST} |
|              | Log | \${NUMBERS}=${NUMBERS} |
|              | Log | \@{NUMBERS}=@{NUMBERS} |
|              | Log | \${NUMBERS}[2]=${NUMBERS}[2] |
|              | Log | \@{NUMBERS}[2]=@{NUMBERS}[2] |
|              | Log | \${MAPPINGS}=${MAPPINGS} |
|              | Log | \@{MAPPINGS}=@{MAPPINGS} |
|              | Log | \&{MAPPINGS}=&{MAPPINGS} |
|              | Log | \${MAPPINGS}[1]=${MAPPINGS}[1] |
|              | Log | \${MAPPINGS}[cat]=${MAPPINGS}[cat] |
|              | Log | \@{MAPPINGS}[1]=@{MAPPINGS}[1] |
|              | Log | \&{MAPPINGS}[cat]=&{MAPPINGS}[cat] |
|              | Log | \${MAPPINGS.dog}=${MAPPINGS.dog} |
#|              | Log | \${AREA1}=${AREA1} |
#|              | Log | \${SOME_VARIABLE}=${SOME_VARIABLE} |
|              | Log | \${USER}=${USER} |
|              | Log | \${RANDOM_INT}=${RANDOM_INT} |
|              | Log | \${CURRENT_TIME}=${CURRENT_TIME} |
|              | Log | \${AFTERNOON}=${AFTERNOON} |
|              | Log | \${AREA1}=${AREA1} |
|              | Log | \${AREA2}=${AREA2} |
|              | Log | Good bye, Cruel World |
