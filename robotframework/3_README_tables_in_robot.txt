Different types of tables in robot
=================================

Settings --> Used to import test libraries, resource file, variables files. Defining metadata for test suites and test cases.
Variables --> 	Defining variables
Test Cases --> Defining test cases.
Keywords --> Creating user keywords from lower-level keywords

All strings are in unicode format in robot. There are a number of built in scalar variables defined in Robot libraries themselves. Examples
1) ${EMPTY} --> Used to indicate an empty cell in a table (may be an empty cell is needed as argument to a keyword for some other purpose).
2) ${SPACE} --> to indicate the presence of a space (not to be interpreted by robot as a delimiter)
3) ${\n} --> platform independent line separator. Will expand to \n on linux and \r\n on windows.


If your rows are getting pretty long, you can divide them into multiple rows by using ellipses (...). For rows in Settings and Variables tables, ellipses can be used as the value in the first column. But for Test Cases and Keywords tables, ellipses must be preceded by an empty cell.
