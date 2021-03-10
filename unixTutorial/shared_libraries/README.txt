Objects in shared library (*.o files) must be compiled with -fPIC option. PIC means Position Independent Code. -fPIC makes the compiler change the way the code is generated. These changes allow the code to be located at any virtual address at run time.

To find if a object file was built with -fPIC, use readelf command to read its symbol table. 
readelf -s mod1.o | grep _GLOBAL_OFFSET_TABLE_  # This means that .o file was compiled with -fPIC option. -s means display the symbol table.

If you have a *.so instead, and want to tell if all object files were compiled with -fPIC, use
readelf -d libfoo.so | grep TEXTREL  # If you get any output, this means that atleast one .o file in the .so was not compiled with -fPIC option.
TEXTREL means that there exists a .o file whose text section contains a reference to requires run time relocation. -d means display the dynamic section.

shared libraries names
=====================

soname: this is a name that you can embed in the shared library when creating it using the -Wl,-soname linker option.
example: gcc -g -shared -Wl,-soname,libbar.so -o libfoo.so mod1.o mod2.o mod3.o

to find out if a shared library soname is embedded in a .so file, use:
readelf -d libfoo.so | grep SONAME

Later when you link this library with an executable, the linker will see if a soname is embedded in the shared library. If yes, it will store the soname in the executable and at run time it will try to find a shared library with the soname.

gcc -g -Wall -o prog prog.c libfoo.so  # although we use libfoo.so at link time, at run time it will try to find libbar.so

Usually if you do "readelf -d libstc++.so.6.0.25 | grep SONAME", it will show libstdc++.so.6, which means it will try to find libstdc++.so.6 at run time. That's why we a soft link with libstdc++.so.6 pointing to libstdc++.so.6.0.25
