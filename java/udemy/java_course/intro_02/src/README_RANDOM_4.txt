What are the main methods on the java.lang.Object()?
=====================================================

toString(), hashCode(), equals()

others:
wait(), notify(), notifyAll()

more:
finalize(), clone()


Difference between String and char[]
====================================
String is a class which provides useful methods. for inspection, modifying, and lookup.
String is immutable. you can get its length using the length() method. Compare String using String.equals()

For char[] it is fixed size, but can still change its contents unlike a String.
Get char[] size using .length, example:
char[] JavaCharArray = new char[5];
JavaCharArray[0] = 'r';
JavaCharArray[1] = 's';
JavaCharArray[2] = 't';
JavaCharArray[3] = 'u';
Compare char[] arrays using Array.equals()

one of the String ctors takes a char[] also as an argument


What is JVM
============
Java virtual Machine
It has:
GC (Garbage Collector) -> Handles memory allocation and destruction
JIT (Just in Time Compiler) --> will optimize your code and convert to machine code
Has a security mechanism so that one malicious code from outside can creep into the JVM.
HotSpot is the JVM name from OpenJDK.