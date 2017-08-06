Generator expressions allow you to evaluate some values at the build generation phase. Most often the generator expressions are applied to TARGET properties like
1) LINK_LIBRARIES
2) INCLUDE_DIRECTORIES
3) COMPILE_DEFINITIONS etc..
or can be used in commands which set these properties like target_link_libraries(), target_include_directories(), target_compile_definitions() etc.

Generator expressions are not evaluated at configure time (when CMake is parsing CMakeLists, executing commands like add_target(), message(), set() etc.). At this time, a generator expression is just a literal string - the character $ followed by <, then T, then ...

Evaluation of generator expressions happens at generate time (that's why they are called "generator expressions"). Generate time occurs after all CMake code is parsed and processed, and CMake is starting to act on the data therein to produce buildsystem files. Only then does it have all the information necessary to evaluate generator expressions.

So you can only really use generator expressions for things which occur at generate time or later (such as build time).

The benefit of using them is that they allow conditional compiling, linking, include directories etc.
like for example, link certain libraries in only DEBUG mode etc. The syntax is pretty simple:

$<$<CONFIG:DEBUG>:DEBUG_MODE>  -> ie this generator expression will evaulate to 'DEBUG_MODE' is CONFIG is DEBUG.

Many types of generator expressions exist. Lets see them in a 2_README.txt


