Scons has a number of builder functions which are special functions to tell scons how to build a target.
Lets study a few first

Object
======

Object() function is used to create a .o file
Object('hello.c') will create hello.o

Program
========
Program() - There are many different ways you can call this function

Program('hello.c') - Make executable hello using hello.c
Program(['hello.c']) - Same as above. Can specify list also
Program(['foo.c', 'common.c', 'utils.c']) - Make executable foo(name based on first item in list), using foo.c, common.c and utils.c
Program('new_hello', 'hello.c') - Make executable new_hello using hello.c
Program(target='new_hello', source=['a.c', 'b.c', c.c'])

src_files = Split('a.c common.c x.c') - Split is a function which splits the string based on whitespace. If argument is not a string, then return the argument as a list.
Program('hello', src_file) - Make hello from a.c, common.c and x.c

Program('hello', Glob(*.c)) - Make hello using all *.c files found in the current directory (not recursively)
Program(Split('''foo.c
               xyz.c hello.c''')) - Make foo from foo.c xyz.c and hello.c
You can also use multiple Program() functions in the same scons file.


Library or StaticLibrary (no difference, use anyone)
========================
Used to create a static archive
Library('foo', ['foo.c', 'common.c']) - Make libfoo.a from foo.c and common.c
Library('foo', ['foo.o', 'common.o']) - Make libfoo.a from foo.o and common.o. Make sure you have a rule for creating foo.o and common.o, otherwise scons will assume that
these files already exist


SharedLibrary (to create a .so file)
=============
scons will automatically add --shared option and also create .so output
SharedLirary('hello', Split('hello.cpp'))


Depends
=======

In cases where scons is not able to detect a dependency of hello on "foo.cpp" you can explicitly use the Depends() function
Depends(hello, Split('foo.cpp')) - the second argument can also be a list of Nodes.
