#!/usr/bin/env python3

# When creating a python string literal \n and other special characters
# can be used. For eg:
str = 'Hello\nanny'
print(str)  ## will print
            ## Hello
            ## anny
# So \n does a line break.
# But if you want to literally print 'Hello\nanny', then you have to use 2 backslashes.
str = 'Hello\\nanny'
print(str)  ## print 'Hello\nanny'

# Now to write a regular expression pattern to match a literal '\' in a python string,
# you'll have to match two backslashes occurring togther (as that will mean a single backslash)
# since regular expressions themselves use a \ character for escaping. the pattern will be
# '\\\\' meaning '\\' which means '\' in a python string.

# To avoid this confusion, the best is to use python's raw string notation for writing
# regular expression
# So r"\n" is a two character string consisting of \ and n

# Python regular expressions

# .   -->  Any character
# ^   --> Match at start of string
# $   --> Match at end
# *   --> Zero or more occurrences of preceding characters
# +   --> One or more
# ?   --> Zero or One
# Remember * + and ? are all greedy matchers, They match as much text as possible
# So in string '<H1>title</H1>', RE '<.*>' will match the whole string.
# The other way is to instruct these RE to match as little as possible. For that used

# *?, or +? or ?? --> as the case may be, so '<*?>' will match '<H1>' above.
# {m} --> Match m occurrences of the preceding RE
# {m,n} --> Match m to n (both inclusive). If m is omitted, assume 0. if n is omitted assume infinite.
# {m,n}? --> Same as above but match as few as possible. Eg: for string 'aaaaaa', RE 'a{3,5}?'
#            will match 'aaa'
# \  --> \*, \+ or \? can be used to match *, + or ? literraly
# [amc] --> match either a or m or c
# [a-z] will match any lowercase alphabet, [0-9A-Fa-f] --> will match any hexadecimal digit
# [a\-z] ->will match a or - or z. Note that \ is used to escape -
# Very important, special characters will loose their meaning in sets, so
# [(+*?)] will match any character ( or + or * or ? or )
# [^a-z] -> will match any character other than a-z
# [()[\]{}] or []()[{}] --> will match any paranthesis ( or ) or { or } or [ or ]
# | --> A|B will match RE A or RE B

# Many times you can use extra flags supported by this module to modify your regular expression.
#  These flags should be are specified like '(?<alphabet>)'. The currently supported alphabets are:
#  (?i) --> to do case insensitive search
#  (?a) --> ascii only matching
#  (?L) --> lacale dependent matching
#  (?m) --> multi-line expression
#  (?s) --> match all
#  (?x) --> verbose
#  If you dont want to use these flgas, then you can specify these flags explicitly in
#  the re.compile() function as you'll see later.


#  (?:<pattern>) -- Patch pattern in paranthesis but group will not be captured and you cannot use it later like \1 \2 etc.

# (?P<name>...) --> this syntax is used to create a sub-group which also has a name. Can be used later either like
#  \1 or with its name also.
#  Eg: To match a string which is inside single or double quotes, use
# (?P<quote>['"]).*?(?P=quote) --> Very trivial actually
# (?P<quote>['"]).*?\1 --> also is the same as above exept that it uses the numbered form instead of name form
# If you are using the above expression to match and you get back a match object/group. you can access that group using
# m.group('quote') or m.end('quote') etc.
# In the replacement string, you can use \1 or \g<1> or \g<quote>
# Dont worry its very easy as you'll see examples soon.

# To explain your regular expression to other users, use
# (?#...) : this is a comment and will be ignored alltogther. Beautiful

# Complex stuff now.
# (?=<pattern>) will match if <pattern> matches next. So if you have string 
# 'Rajat Girotra' and 'Rajat Malhotra',
# then 'Rajat (?='Girotra')' will match first 'Rajat ' and not the second 'Rajat '

# Exact opposite of above is (?!<pattern>)

# (?<=<pattern>) --> Is called positive lookbehind assertion.
# Matches if the current string position in the string is preceded by a match for <pattern>
# So in 'abcdef', RE '(?<=abc)def' will match and m.group(0) will return 'def'
# Similarly
# in string 'spam-egg' to extract egg you can write a RE '(?<=-)\w+' and m.group(0) will return 'egg'

# Exactly opposite of above is called negative lookbehind assertion.
# (?<!<pattern>)

# (?(id/name)yes-pattern|no-pattern)
# If the given id or name exists, with try to match <yes-pattern>, otherwise try to match no-pattern.
# Also no-pattern is optional.
# Let's write a pattern to match email id which is optionally surrounded by carets. ie
# rajat_girotra@gmail.com or <rajat_girotra@gmail.com>
# Pattern = '(<)?(\w+@\w+(?:\.\w+)+)(?(1)>|$)

# \1 \2 etc --> you already know.
# \d - matches [0-9] and many other Unicode digit characters. If you dont want to match Unicode digit characters
#      turn on the ASCII flag (but it will affect the whole expression); or better use [0-9] explicitly.
# \D -- opposite of \d

# \w - match any unicode word character and number and underscore. If ASCII flag is set, match only [a-zA-Z0-9_]
# \W - opposite of \w

# \s - matches a unicode whitespace (ie [<space>\t\n\r\f\v]
# \S - opposite of \s

# \b - match the empty string, but only at the beginning or end of a word; where a word is defined as \w
#      So if RE is '\bfoo\b', then it will match 'foo', 'foo.', '(foo)' but not 'foobar' or 'foo3'
# \B - match the empty string, only when it is not the beginning or end of a word.
#      Just opposit of \b. Soo r'py\B' will match 'python', 'py3', 'py2', but not 'py.', 'py', 'py!'

# \A - matches only at the start of the string
# \Z - matches only at the end of the string.
