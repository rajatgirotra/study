http://rachid.koucha.free.fr/tech_corner/cmake_manual.html

What is CMAKE.

It is a cross platform build system which generates makefiles native to the operating system.
So on linux, you can specify cmake to generate Makefiles, on Windows you can direct it to make
Visual Studio project files. etc.

There are a number of options you can specify to cmake.
Do cmake --help for more.

In cmake, we have a source tree and we have a binary tree. Binary tree is the location where all the
artifacts (target files, shared libraries etc) are generated. Best is to keep these two locations
separate so as not to populate your source tree.

In cmake, we write files with the name CMakeLists.txt
These are files which specify how the targets are to be built. CMake uses its own language to specify
the contents of CMakeLists.txt

the cmake language consists of
1) commands: try "cmake --help-command-list" or "cmake --help-command set"
2) variables: try "cmake --help-variable-list" or "cmake --help-variable <variableName>"
3) properties: Similar options as above.
4) modules: Similar options as above.


We can run CMAKE in mutiple ways.

1) Using GUI. is dependent on QT. Use cmake-gui command to bring up an interface for managing your project artifacts
2) Using terminal. Run ccmake. Similar to gui interface but runs in terminal
3) Manually: using "cmake -i" (for running interactively) or "cmake" for running non-interactively.  This is deprecated and no longer supported.
