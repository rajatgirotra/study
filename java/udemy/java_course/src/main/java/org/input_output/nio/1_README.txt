java new input output classes were written with only one goal in mind. Speed. It does it by using data structures which are very close to the operating system.
important classes are Channels and Buffers: Think of a channel as a coal mine with all your data. and think of a Buffer class as a cart that you send into the Channel
for reading and writing.

In fact the java.io classes also internally use java.nio functionality wherever possible.
FileInputStream, FileOutputStream, RandomAccessFile --> all these java.io classes now provide and API "getChannel()" for you to work with Channels and Buffers.

Buffer class
============
A Buffer is a linear, finite sequence of elements of a specific primitive type. Aside from its content, the essential properties of a buffer are its capacity, limit, and position:
1) A buffer's capacity is the number of elements it contains. The capacity of a buffer is never negative and never changes.
2) A buffer's limit is the index of the first element that should not be read or written. A buffer's limit is never negative and is never greater than its capacity.
3) A buffer's position is the index of the next element to be read or written. A buffer's position is never negative and is never greater than its limit.

There is one subclass of the Buffer class for each non-boolean primitive type. Example:
ByteBuffer, CharBuffer, DoubleBuffer, FloatBuffer, IntBuffer, LongBuffer, ShortBuffer

Transferring data
=================
Each subclass of this class defines two categories of get and put operations:

Relative operations
-------------------
read or write one or more elements starting at the current position and then increment the position by the number of elements transferred.
If the requested transfer exceeds the limit then a relative get operation throws a BufferUnderflowException and a relative put operation throws a BufferOverflowException; in either case, no data is transferred.

Absolute operations
-------------------
take an explicit element index and do not affect the position. Absolute get and put operations throw an IndexOutOfBoundsException if the index argument exceeds the limit.

channel operations
-------------------
Data may also, of course, be transferred in to or out of a buffer by the I/O operations of an appropriate channel,
which are always relative to the current position.

Marking and resetting
=====================
A buffer's mark is the index to which its position will be reset when the reset method is invoked. The mark is not always defined, but when it is defined it is never negative and is never greater than the position.
If the mark is defined then it is discarded when the position or the limit is adjusted to a value smaller than the mark.
If the mark is not defined, then invoking the reset method causes an InvalidMarkException to be thrown.

Invariants
==========
The following invariant holds for the mark, position, limit, and capacity values:
0 <= mark <= position <= limit <= capacity
A newly-created buffer always has a position of zero and a mark that is undefined. The initial limit may be zero, or it may be some other value that depends upon the type of the buffer and the manner in which it is constructed.
Each element of a newly-allocated buffer is initialized to zero.

Read GetChannel.java next