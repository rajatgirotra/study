We have a simple login.py code for which we want to write test cases. This login.py utiliy is used to register new users and also authenticate users. Commands that you can execute are:

python login.py login <username> <password>
python login.py create <username> <password>
python login.py change-password <username> <old-password> <new-password>

The new password must be 7-12 characters long

Running Robot
=============
is super easy.

robot [options] [robot test files/directories]  # robot is a helper script which invokes the robot python module
OR
python -m robot [options] [robot test files/directories]

"Tests are contained in files or directories containing one or more test case files. Test cases in a file are together called a test suite and multiple tests case files in a directory form a higher level of test suite".
Test case directories can have a special initialization file. (__init__.robot, similar to __init__.py in python).
Test case initialization files can have very similar Settings as the Settings table in the test case file. It CANNOT have test case tables.

Robot Output
===========
By default, robot generates output in XML format and html format. But this can be customized using options. typical output files are
1) report.html
2) log.html
3) output.xml

Different types of files in Robot
================================
Library files: These contain the lowest level of keywords
Resource files: These can contain variables and other higher level keywords
Variable files: These provide more flexible ways of creating variables compared to resource files.

Robot Test case file format
===========================
This can get complex. Multiple formats are supported
1) HTML: files with extension .html, .htm, .xhtm
2) TSV (Tab separated files): files with extension .tsv
3) Plain text: files with format .txt and .robot
4) reST format ->reStructuredText format: files with format .rst, .rest

Each format has its pros and cons. Plain text format is usually preferred. For HTML and TSV formats, all data must be in the form of tables. All data outside of tables is ignored. The type of the table is identified by the value in the first cell. For TSV tables, the value in the first cell must be an asterik (*) followed by the table name. There are different types of tables, as you'll see later.

Plain text format is also similar to the TSV format. In TSV separator is a tab, in plain text format, SEPARATOR IS TWO OR MORE SPACES OR A PIPE CHARACTER SEPARATED BY A SPACE ON BOTH SIDES. TABLES ARE ALSO IDENTIFIED BY VALUE IN THE FIRST CELL, AND THAT VALUE MUST START WITH ONE OR MORE ASTERIKS. Example: *** Settings *** and *Settings is same.

What if you have a cell with empty value. How will robot know that it is a cell with empty value not just a separator??
use the special ${EMPTY} variable or use a single backslash \. If spaces make it difficult to see cell boundaries, better to use pipe separator with space on both sides.

for pipe and space delimited rows, the row must start with a leading pipe character. Also pipe and space give u the advantage that you no longer need to escape empty cells with ${EMPTY} and backslash. But if you have a pipe as a value in your cell, that needs to be escaped using \. Example: "ls -ltr \| wc -l"
