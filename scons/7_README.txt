Functions controlling dependencies
=================================

Depends
=======
Depends(hello, 'versoin.cpp') - Sometimes scons is unable to determine the target dependency correctly. In those cases, you can use Depends() function to explicitly
state that hello is dependent of version.cpp


ParseDepends
===========
ParseDepends() - scons tries to calculate implicit dependencies by looking at the #include files in the source file. But if you do something like this in a source file/=:
#define FOO_HEADER <foo.h>
#include FOO_HEADER

then scons cannot determine that the source file depends on foo.h (scons is not a full-fledged c preprocessor). In those cases, you can use the compiler to specify the correct
dependencies list (using the -MMD -MF flags, just like in make). This is what you have to do:

obj_list = Object('hello.o', CCFLAGS = '-MMD -MF hello.d')
SideEffect('hello.d', obj_list)  -->   Use SideEffect function to tell scons to generate a file called hello.d when hello.o is generated.
ParseDepends('hello.d') --> Parse hello.d (which will tell which files depend on which other files)
Program('hello', obj_list) --> Build hello executable normally



Requires
========

Requires() is a way of telling that a dependency is an order only dependency, which means that the target file should not be rebuilt, if the file in the Requires() function
is changed or out-of-date. It only means that the file should be available before the target is built. Same effect as you get using the "|" symbol in make dependencies.
Requires(hello, obj_list) --> obj_list should must be present before hello is built.


Ignore
=======
Explicitly state to ignore a dependecny
Ignore(hello, 'version.cpp') --> Dont make hello executable depend on version.cpp


AlwaysBuild
==========
Very trivial
AlwaysBuild(hello) --> Means always build hello when it is specified as a target on the command line.
