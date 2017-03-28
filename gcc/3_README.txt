Link Time Optimization
======================

gcc has a feature where it can delay optimization until link time rather than at compile time.
Apparently, when all the compilation units are merged together as one executable, it gives gcc the advantage to optimize the whole program
together instead of optimizing different object files. This leads to better optimization as the linker is able to see much more code together
as opposed to the compiler which sees only single translation units.

How it happens
==============

Very simple. Compile your code with the "-flto" option. This causes gcc to store it own internal representation
called GIMPLE to the object files (ELF files). Also specify the optimization level.
At link time, the linker must also use the "-flto" option. This causes the linker to detect the presence of GIMPLE sections in ELF and then it performs optimization.
This is currently done by collect2 which is a wrapper or ld. Also specify the optimization level.

g++ -c -O3 -flto -o abc.o abc.cpp
g++ -c -O3 -flto -o xyz.o xyz.cpp
g++ -c -O3 -o lmn.o lmn.cpp
g++ -O3 -flto -o myprog abc.o xyz.o lmn.o

gcc linker is clever to find out which object files have GIMPLE sections and should be optimized. So we can mix object files with or without GIMPLE sections.
However if you explicitly choose "-fno-lto" then no link time optimization will occur for abc.o and xyz.o

Obviously, object files compiled with "-flto" will be larger as they contain GIMPLE bytecode.

Problem
=======

What if I want to store object files (with "-flto") into an static archive. How will these get optimized at link time.
It turns out you need to use another compiler flag "-fuse-linker-plugin". This basically enables the linker to read object files from static
archives for LTO. However, the linker must be built with plugin support. By default i think "ld" linker is built with plugin support
You can also use another gcc linker (called gold) using "-fuse-ld=gold" flag which also perform better.

So now optimization flags in gcc compilation step should be:
-O3 -flto -fuse-linker-plugin -fuse-ld=gold
Also you must use "-fuse-linker-plugin" at link time to ensure static library participates in the LTO process.

gcc -o myprog -O3 -flto -fuse-linker-plugin a.o bo. -lfoo (where libfoo.a) is a static archive.

Now to make static archives which are suitable for LTO, you need to pass a special --plugin option to "ar" command. Do "man ar" and search for plugin
Better still just use the "gcc-ar" command which is a wrapper over "ar" command and will pass the "--plugin" option itself.
gcc-ar cr a.o b.o libfoo.a
or
ar cr --plugin liblto_plugin.so a.o b.o libfoo.a

Other flags
==========

gcc provides a flag "-ffat-lto-objects" which created objects files with both optimized code and with GIMPLE bytecode. This can be used to create static
archives which may then be used with or without LTO optimizations
