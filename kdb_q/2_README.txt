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

char --> size 1 --> char c --> number 10 --> "z" --> " " (yes a blank character is Null in KDB/Q. "" is an empty character, not treated as null in KDB/Q)

symbol --> size variable --> char s --> number 11 --> `helloWorld --> ` (just backtick is null)

date --> size 4 --> char d --> number 14 --> 2025.10.10 --> 0Nd (null date) , dates are just integers under the hood. They are called temporal data.

datetime --> size 8 --> char z --> number 15 --> 2025.10.10T09:09:09 --> 0Nz (null datetime) , dates are just long under the hood (note that this type is deprecated. Prefer to use timestamp)

timestamp --> size 8 --> char p --> number 12 --> 2025.10.10D00:00:00.000000000 --> 0Np (null timestamp) 

timespan --> size 8 --> char n --> number 16 --> 12:10:30.123456789 --> 0Nn (null timespan) 

list is negative of type of list

table is number 98 --> ([]sym:`APPL`GOOG;price:100 200)

dictionary is 99 --> `a`b`c!10 20 30

function is 100 {x}

nil item is 101  ::

Negative float infinity: -0w
Positive float infinity: 0w
Nan float infinity: 0n

Negative long infinity: -0W
Positive long infinity: 0W
Nan long infinity: 0N


real values i.e. 4 byte floats having single precision are useless in finance. always prefer floats which offer double precision i.e. upto 15 digits after decimal (although the last digit is unreliable). By default q round decimal values to 7 places but more precision is available. You can use the system command \P to set your required precision.

char data type just holds a single character in ASCII or Unicode. special characters can also be stored using escape sequence \.
Example: "\"" for quotes, "\\" for backslash, "\r, \n, \t" for line feed, tab, new line etc.

Symbol and strings are different in Q. Symbols cannot be broken down into characters. they are precided by a back tick. Example: `helloworld. Symbols can have blanks and special chars too.
strings are a sequence of characters enclosed inside quotes. You can create a symbol from a string using casting. Example:

`$"a very long symbol with blanks"

Remember symbol and string are not the same in Q.

Dates
=====
As I said before dates are temporal data which means they are just integers under the hood. Date at start of millenium i.e. 2000.01.01 is assigned 0, previous daates are negative number, later dates are positive dates.

time is represented also as 32 bit integer. Format of time type is hh:mm:ss.uuu i.e. use it if upto millisecond is enough
if milliseconds is not enough, use timestan type which is upto nanoseconds. it presents nanos from midnight.
q)14:39:00.123456789
0D14:39:00.123456789

q) `long$14:39:00.123456789 / cast to nanos from midnight.

timestamp --> this type is a lexical combination of both date and timespan type. it represents nanos from millenium. again after 2000.01.01 are +ive and before are -ive. Under the hood is a long type. It can also be casted like shown below.

q)now_ts: 2014.11.22D17:43:40.123456789
q)long_nanos: `long$now_ts
q)show `long_nanos
q)now_ts: `timestamp$long_nanos
q)show `now_ts

Similarly you have month, minute and second types.

q)x: 2000.01m
q)`int$x / will show 0

q)`int$1982.09m / your birth month in KDB. :) will be negative
-208i

q)12:30 / minute type in hh:mm
q)23:59:59 / second type in hh:mm:ss

q) dt:2026.02.07D12:26:52.678123002
q) / cast the date above to get the year, month and day
q) show `year$dt / 2026i
q) show `mm$dt  / 2i
q) show `dd$dt  / 7i
q) show `month$dt / 2014.01m
q) show dt.hh / 12i
q) show dt.mm / doesn't Extract minute. Shows month instead. Find the answer
q) show dt.ss / 52i
q) (`long$dt) mod 1000000000 / get nanos (mod by 1000 to get the milliseconds if you have time type)

Testing for Nulls
=================
You could test for null using = but this requires a null literal of correct type like 0Nn, 0Nd, 0Np etc. Because q is dynamically typed, this can result in problems if a variable changes type during program execution. So best way to check for nulls is to use the "null" keyword.

q)null 42
0b
q)null `
1b
q)null " "
1b
q)null ""
`boolean$()
q)null 0N
1b
