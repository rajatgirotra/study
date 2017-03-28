#!/usr/bin/env python3.2
# Showing usage of strings.

>>> spam eggs    ---->> Must encode string
  File "<stdin>", line 1
    spam eggs
SyntaxError: invalid syntax

---------------------------------------------------

No Need to thouroughly understand below examples.
They are a bit wierd. But just understand in general
that double quotes needs to be escaped using single quotes
and vice versa.

>>> 'spam eggs'
'spam eggs'
>>> "doesn't"
"doesn't"
>>> 'doesn\'t'
"doesn't"
>>> "abcd"
'abcd'
>>> '"Yes", she said.'
'"Yes", she said.'
>>> "\"Yes\", she said."
'"Yes", she said.'
>>> '"I" can\'t'
'"I" can\'t'
>>> '"I" can\' t'
'"I" can\' t'
>>> "I" 'can\'t'
"Ican't"
>>> "I " 'can\'t'
"I can't"
>>> '"I "' 'can\'t'
'"I "can\'t'
>>> '"I" ' 'can\'t'
'"I" can\'t'
>>> '"I" ' + 'can\'t'
'"I" can\'t'
>>> "I" 'can\'t'
"Ican't"
>>> "I" ' can\'t'
"I can't"

----------------------------------------------------

"Usage of the backslash to go to a new line. Also note that space are maintained."

>>> hello = "This is an unsual way to say\
...       HELLO"
>>> print (hello)
This is an unsual way to say      HELLO


"Strings can me multiline. Use \n for that"

>>> hello = 'This is a very strange way of saying\n\
... hello'
>>> print (hello)
This is a very strange way of saying
hello

----------------------------------------------------------

Very good way of printing strings. Just enclose within triple quotes"
>>> print("""\
... Usage: thingy [OPTIONS]
...       h: print this help message
...       k: You want to dance
...       j: You want to sleep
... """)
Usage: thingy [OPTIONS]
      h: print this help message
      k: You want to dance
      j: You want to sleep
----------------------------------------------------------
"There is something called as a raw string", defined with a leading r.

>>> hello = r"This is a rwa string with new line and backslash\n \
... displayed as is"
>>> print(hello)
This is a rwa string with new line and backslash\n \
displayed as is

--------------------------------------------------------
Concatenating strings

>>> 'str' 'ing'
'string'
>>> 'str'.strip()  --> The strip API by default strips spaces on both ends.
'str'
>>> '       str'.strip()
'str'
>>> '     e2  str'.strip()
'e2  str'
>>> '    str   '.strip()
'str'
>>> '    strip   danc  '.strip()  + 'ing'
'strip   dancing'
>>> _
'strip   dancing'
>>> 'strip dancing'
'strip dancing'
>>>

Mutiplying a string using *
>>> word = 'HelpA'
>>> '<' + word*5 + '>'
'<HelpAHelpAHelpAHelpAHelpA>
-------------------------------------------------------------------

Indexing strings .

>>> word = 'HelpA'
>>> word[0]
'H'
>>> word [2]
'l'
>>> word[3]
'p'
>>> word[4]
'A'
>>> word[5]
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
IndexError: string index out of range


>>> word[0:2] --> From index 0 to 1
'He'
>>> word[2:4]  --> From index 2 to 3
'lp'
>>> word[:2] --> From starting to index 1
'He'
>>> word[4:]  --> From index 4 to end.
'A'
>>> word[2:] 
'lpA'
>>> word[:]
'HelpA'
>>> word
'HelpA'


>>> word[0] = 'x'
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'str' object does not support item assignment
>>>
>>> newWord = 'x' + word[1:]
>>> newWord
'xelpA'
>>> 'Splat' + word[4]
'SplatA'


>>> word[1:2000]  --> Very big indices are automatically converted to last index
'elpA'
>>> word[10:]
''
>>> word[2:1]
''


Negative indexes.
>>> word
'HelpA'
>>> word[0]
'H'
>>> word[-0]
'H'
>>> word[1]
'e'
>>> word[-1]
'A'
>>> word[-5]
'H'
>>> word[-6]
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
IndexError: string index out of range

Length of a string
>>> len(word)
5
-------------------------------------------------

Unicode and Strings

You can now create a a string with the unicode code point embedded in it
using the \u<Unicode-Code-point> syntax
