Different hierarchy of I/O classes in Java:
===========================================

first hierarchy
---------------
The first hierarchy of classes allows you to read raw bytes from a stream (byte stream classes). The hierarchy of classes is:

InputStream (subclasses must provide a "int read()" method which reads the next byte of data from the input stream)
 |          ( a value between 0 and 255 is returned. -1 is returned on end of stream)
 |
 |__ FileInputStream | ByteArrayInputStream | StringBufferInputStream | FilterInputStream | SequenceInputStream and others

A FilterInputStream contains some other input stream, which it uses as its basic source of data, possibly transforming the
data along the way or providing additional functionality. There are many subclasses of FilterInputStream which actually do that
transformation.

FilterInputStream
 |
 |__ BufferedInputStream | CipherInputStream | DigestInputStream | LineNumberInputStream etc.

second hierarchy
---------------
The second hierarchy of classes allows you to read characters from a stream (character stream of classes). The hierarchy of classes is:

Reader
 |
 |__ BufferedReader | CharArrayReader | FilterReader | InputStreamReader | PipedReader | StringReader

The InputStreamReader class is important here: It is actually a bridge between the raw byte stream and character stream classes. It reads
bytes and converts them to characters using the Charset provided during construction. It may read more than one byte to efficiently convert
bytes to characters. You can even wrap an InputStreamReader inside a BufferedReader for more efficiency.

"BufferedReader reader = new BufferedReader (new InputStreamReader (System.in));"

Java also provides a convenience class "FileReader" which extends InputStreamReader. This class is used for reading characters in the
default Charset and with default byte-buffer size.

"BufferedReader reader = new BufferedReader (new FileReader ("foo.txt"));" # still good to wrap in BufferedReader for efficiency.