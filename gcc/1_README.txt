Important gcc flags to use:

Typical flags to use
====================
-Wall - Turn on all warnings
-Wextra - Turn on extra warnings
-Werror - Make warnings as erros
-Wconversion - Error on implicit conversions which might alter a value
-fPIC - Build Position independent code.
-isystem <dir> : Search dir for include files after searching all paths specified by -I option
BUT before searching any include file in the standard system directories. Also mark this dir as a system directory.

Flags for Makefile production
=============================
-MM  : print a rule that can be put in a makefile. Implies -E
-MM -MG : -MG means assume that header files which are not available as files which will be produced. So output the result anyway.
           This means using -MG will not compile or preprocess your code
-MF <file> : Filename to output the make rule to. Implies -E
-MT <target> : Name of the dependency target. By default it is abc.d for file abc.cpp
-MMD : means -MM -MD, is same as -MM -MF except that -E is not implied. So -MMD will compile your code.

Standard specification
======================
-std=c++11 or -std=gnu++11 (for c++11 with gnu extension), c++1y (for next standard ie c++14), gnu++1y(for next c++ standard with gnu extensions)

Deugging flags
=============
-g<number> or -gdb<number> - Request debugging information and also specify how much information is needed by specifing a level
-g or -ggdb0 : means no debugging information
-g1 or -ggdb1
-g2 or -ggdb2
-g3 or -ggdb3 : means maximum information
-fsanitize=address : Enable address sanitizer : A fast memory error detector
-fsanitize=thread : Enable Thread sanitizer: A fast data race detector.
-fsanitize=leak : Enable Leak sanitizer : A fast memory leak detector
-fsanitize=undefined : Enable UndefinedBehavior sanitizer

Diagnostics
===========
gcc can print diagnostic information
-fdiagnostic-show-option : Each diagnostic emitted will include text indicating the command-line option that directly controls the diagnostic.
-fdiagnostics-color<WHEN> : never, auto, always. Use to show diagnostics information in color. I dont yet know what are diagnostoics.
                            But I will find out eventually.

Optimization
============
-O0 : Minimium or no optimization. Make gdb produce expected results.
-O1
-O2
-O3 : Maximum optimization
If you use -O3 -ggdb3. it is not a problem, but -O3 will optimize out a lot of code so debugging might not produce expected results.
Another option is 
-Og : ie optimize of debbuging. Meaning do not optimize away debugging symbols. This should be the default when doing edit-compile-debug cycles.
      Later you can change it to -O3 
PLEASE PLEASE READ 3_README.txt as it has very important optimization discussion.

Architecture
===========
-m32 : Force gcc to compile a 32 bit application. Using this option will force the stack frame, data and constants to be 32 bit aligned.
       So size of pointer and size of long will be 4 bytes.
       Make sure for this you have installed 32 bit libraries for gcc using sudo apt-get
-m64 : Similar but everything will be 64 bit aligned.

To make sure that gcc can build 32 bit target applications on 64 bit system, gcc should be compiled with multilib support.
An easy way to check is:
-print-multi-lib: Will print the mapping from multilib directory names to the compiler switches that enable them. 

-m32 -print-multi-os-directory: Prints the paths to the OS libraries that will be used when linking with the specified multilib. This
                                will print the paths relative to the /usr/lib/
-m32 -print-multiarch: Same as above

-m32 -print-multi-directory: Prints the directory name corresponding to the multilib option specified.

Multiarch is basically the ability of a system to install and run applications for different binary targets on the same system.
Like running an i386-linux-gnu application on an x86_64-linux-gnu architecture.

Linking
=======
-Wl,option : "option" is a comma separated list of options to be passed to the linker (by splitting at the commas)
             -Wl,-rpath,lib will pass "-rpath lib" to the linker.
--static : Instruct linker to use the static version of a library instead of dynamic (which is the default)
--shared : Instruct linker to produce a shared version of the library
-rdynamic: Instruct the linker to add all symbols to the dynamic symbol table, not just the ones those are used. Is required in some cases 
           where we use dlopen() or to obtain backtrace from within a program.
-l:<libraryName> : Search library paths for a library with exactly the name specified.

"lsb-release -i" command  gives you the distribution
