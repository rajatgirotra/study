/**
 * In C++ (and C), the #line directive is a preprocessor directive used to change the compiler’s idea of the current line number and/or filename.
 * #line line_number "optional_filename"
 * line_number → the new line number the compiler should treat the next line as.
 * "optional_filename" → (optional) the source filename string the compiler should use in error messages, warnings, and debugging info.
 * #line lets you override these, which is useful if your code is auto-generated (from a parser generator, code generator, macros like Boost PP) and you want compiler
 * errors to refer to the original source, not the generated file.
 *
 * The BOOST_PP_LINE macro places notes encoded as line directives in the preprocessing output.
 * Suppose you are generating code inside a Boost PP macro and want compiler errors to point to the calling location, not deep inside the macro expansion:
 */

