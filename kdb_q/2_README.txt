Data types in Q
In Q every data type is given a unique "char" value and a unique number. each type also has a size. Null values in a particular type are also represented differently.
main types in q are:

boolean --> size 1 --> char b --> number 1 --> 0b or 1b

byte --> size 1 --> char x --> number 4 --> 0x00 (null)

short --> size 2 --> char h --> number 5 --> 42h --> ONh (null)
int --> size 4 --> char i --> number 6 --> 42i --> ONi (null)
long --> size 8 --> char j --> number 7 --> 42j --> ONj (null)

real --> size 4 --> char e --> number 8 --> 4.2e --> 0Ne (null)
float --> size 8 --> char f --> number 9 --> 4.2 --> 0n (null)

char --> size 1 --> char c --> number 10 --> "z" --> " "
symbol --> size variable --> char s --> number 11 --> `helloWorld --> ` (just backtick is null)

date --> size 4 --> char d --> number 14 --> 2025.10.10 --> 0Nd (null date) , dates are just integers under the hood
datetime --> size 8 --> char z --> number 15 --> 2025.10.10T09:09:09 --> 0Nz (null datetime) , dates are just long under the hood
timestamp --> size 8 --> char p --> number 12 --> 2025.10.10T00:00:00.000000000 --> 0Np (null timestamp) 
timespan --> size 8 --> char n --> number 16 --> 12:10:30.123456789 --> 0Nn (null timespan) 

list is negative of type of list
table is number 98 --> ([]sym:`APPL`GOOG;price:100 200)
dictionary is 99 --> `a`b`c!10 20 30
function is 100 {x}
nil item is 101  ::

real values i.e. 4 byte floats having single precision are usefless in finance. always prefer floats which offer double precision i.e. upto 15 digits after decimal (although the last digit is unreliable). By default q round decimal values to 7 places but more precision is available. You can use the system command \P to set your required precision.

char data type just holds a single character in ASCII or Unicode. special characters can also be stored using escape sequence \.
Example: "\"" for quotes, "\\" for backslash, "\r, \n, \t" for line feed, tab, new line etc.

Symbol and strings are different in Q. Symbols cannot be broken down into characters. they are precided by a back tick. Example: `helloworld. Symbols can have blanks and special chars too
string are a sequence of characters enclosed inside quotes. You can create a symbol from a string using casting. Example:

`$"a very long symbol with blanks"

Remember symbol and string are not the same in Q.

