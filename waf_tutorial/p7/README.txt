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

c_config:
C/C++/D configuration helpers

c_aliases:
base for all c/c++ programs and libraries

cxx:
Base for c++ programs and libraries

compiler_cxx:
Try to detect a C++ compiler from the list of supported compilers (g++, msvc, etc):


