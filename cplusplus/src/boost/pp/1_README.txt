Boost PP has a mechanism called file iteration. Basically what Boost PP can do is re-include the same file multiple times - each time with a different macro value (or loop counter). This is how it can emulate loops in Boost PP. When a Boost PP loop is active, the BOOST_PP_IS_ITERATING macro is 1. When the file is included first time by the compiler/preprocessor, this macro will evaluate to 0.

BOOST_PP_IS_ITERATING --> set to 1 if file iteration is in progress
#include BOOST_PP_ITERATE() --> Used to trigger file iteration (i.e. re-including the same file). See below the _n macro meanings
BOOST_PP_ITERATION_DEPTH() --> returns the current nested depth of the file iteration. think of multiple nested for loops. Outer loop will have depth 1 and inner loop will have depth 2.
BOOST_PP_ITERATION() --> returns the current loop counter of the current iteration.

Boost uses BOOST_PP_ITERATION_PARAMS_n macros (where n is 1–5) to pass iteration parameters into the BOOST_PP_ITERATE() machinery.
#define BOOST_PP_ITERATION_PARAMS_x (c, (start, finish, filename [, flags]))
x → the iteration depth of the next file iteration. this value must be the current iteration depth + 1.
c → the number of parameters (will be 3 or 4 only).
(start, end, "filename.hpp" or <filename.hpp>) → a tuple describing the iteration range and file to include.
flags --> The flags associated with this file-iteration used to discriminate between different file-iterations in the same file.
example: #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, 3, "file.h"))
depth = 1 (_1 suffix)
There are 3 parameters
The iteration runs from 1 to 3, inclusive.
The file to iterate is file.h.

When you invoke: "#include BOOST_PP_ITERATE()"
Boost figures out:
“Okay, depth=1, range=1..3, and file=file.h.”
So it repeatedly includes file.h three times, once with:
BOOST_PP_ITERATION_DEPTH() = 1
BOOST_PP_ITERATION() = 1, 2, 3 (each pass)
And BOOST_PP_IS_ITERATING defined during those passes.

Instead of using one macro, you can also use separate macros for the same.
#define BOOST_PP_ITERATION_LIMITS (1, 3)
#define BOOST_PP_FILENAME_1 "file.h"
#include BOOST_PP_ITERATE()
The above code has the effect of including "file.h" three times in succession.