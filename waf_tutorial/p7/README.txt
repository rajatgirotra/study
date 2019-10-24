# Very important concept here. Read carefully

waf provides many different extension modules (called Waf tools) for building projects of different programming languages. A list of important waf tools modules is here:
https://waf.io/apidocs/py-modindex.html

the modules used for C/C++ are 
waflib.Tools.ccroot
waflib.Tools.compiler_c
waflib.Tools.compiler_cxx
waflib.Tools.cxx
waflib.Tools.c_config
waflib.Tools.c_aliases
and may be more.

ccroot: provides low level functionality which other tools like c, cxx, compiler_c, compiler_cxx use.

c_config: VERY VERY IMPORTANT.
C/C++/D configuration helpers

c_aliases:
base for all c/c++ programs and libraries. You will hardly needed. Just defines some convenience wrappers which I think arent that important.

cxx:
Base for c++ programs and libraries

compiler_cxx:
Defines a dictionary of hosts to compilers. and then tries to find a compiler out of the list of compilers for that host.
You can also define your own list of compilers to find. Its very trivial.
Try to detect a C++ compiler from the list of supported compilers (g++, msvc, etc):


