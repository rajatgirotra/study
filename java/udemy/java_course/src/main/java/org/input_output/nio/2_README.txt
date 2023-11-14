UsingBuffers.java first

Memory mapped files provide an interface to read/write very large files which would otherwise take a lot of memory to load all at once.
the api allows you to map parts of a file (given a position and the size of file) into memory and read/write that portion of the file.

The FileChannel API provides a function map() which takes a FileMapping mode (READ, READ_WRITE, PRIVATE) and the starting index and size of the mapping.
It will return you a MappedByteBuffer which extends ByteBuffer and provides you all the ByteBuffer functionality. Memory mapped files are significantly
more performant compared to normal I/O classes. and we will see an example next.

See MappedIO.java next