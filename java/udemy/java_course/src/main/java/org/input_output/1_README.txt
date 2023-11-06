Java provides different packages for dealing with Input Output.

Exceptions
==========
A lot of java i/o api's will throw IOException or one of its subclasses. So you will be handling these a lot of times.
A try block must be followed by one or more catch blocks and also an optional finally block.
Also, a single catch block can catch multiple exceptions using a pipe delimiter. Example:

try {
 ...
} catch(NullPointerException | IllegalArgumentsException badData) {
   ...
}

==============================================================================

java.io --> Old style Input and Output
java.nio --> Non blocking Input and Output and also called New Input Output. Always prefer this.

java.io.File and java.io.FileReader are the main classes
FileReader also implements the AutoCloseable interface. which means it can be used with a "try-with-resources" block which was introduced in JDK 1.7

Also, File class objects do not allocate any File Resources as they provide an API around file metadata/attribute and other file operations.
a File object is just a file handler, not a file resource which must be cleaned up using "close()" method.

FileReader class actually opens a File Resource (ie a file descriptor on the OS), so you must remember to the close the FileReader object to free the descriptor.
That's why the try-with-resources was introduced.
================================================================================

in java.nio package the main classes are:

Path --> You should not need to create an instance of Path object by yourself. The "Paths" class defines a number of static functions to create Path objects.
Path objects can represent filesystem directories and files.

Paths --> Just a class with static functions to create Path objects.

Files --> another class with static functions that provide several operations on Path objects.

Benefits of java.nio classes are:
1) Provides async I/O
2) Provides File locking features; also more granular file level locking is available.
3) Provides events of filesystem changes.
4) Symbolic link handling is available
5) Retrieve file metadata and attributes easily.
6) More performant.

Let's look at some code now. Please read FileMethods.java next