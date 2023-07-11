Java now comes with its own shell called jshell. It allows you to quickly test out java code snippets. It is a REPL (Read-Eval-Print-Loop)
i.e.
1) it will read what you have typed.
2) evaluate and run it inside the shell.
3) print the results for you without using System.out.println()
4) Loop again to get next input.

you can learn more by reading help. type /help in jshell. There are commands like
/vars --> which prints the variables in the current session
/list --> list the source code that has executed already.

Primitive Data Types & their corresponding Wrapper classes
==========================================================
byte: Byte
short: Short
int: Integer
long: Long

float: Float
double: Double

char: Character

boolean: Boolean

Wrapper classes give you some metadata about the primitive classes. Like their size, minimum and maximum values.

Underflow and Overflow
======================
integer data types can overflow and underflow. it is not treated as error so you need to be careful.