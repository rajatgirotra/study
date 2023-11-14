package org.input_output.nio;

import java.io.*;
import java.nio.ByteBuffer;

// read 1_README.txt first
public class GetChannel {
    private static final int BSIZE = 1024; // size of a Buffer in which we will read data from the channel.
    public static void main(String[] args)  {
        // write a file
        try(var fc = new FileOutputStream("data.txt").getChannel()) {
            // both the read and write functions take a ByteBuffer object. wrap() is a static function which takes a byte[] array and returns a ByteBuffer object.
           var bytes = fc.write(ByteBuffer.wrap("some text ".getBytes()));
            System.out.printf("Written %s bytes%n", bytes);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // write to same file using RandomAccessFile object.
        try(var fc = new RandomAccessFile("data.txt", "rw").getChannel()) {
            fc.position(fc.size()); // move to end of file.
            var bytes = fc.write(ByteBuffer.wrap(("some more").getBytes()));
            System.out.printf("Written %s bytes%n", bytes);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // now read and print
        try(var fc = new FileInputStream("data.txt").getChannel()) {
            ByteBuffer buffer = ByteBuffer.allocate(BSIZE); // a non-direct buffer
            fc.read(buffer); // go and read from the channel.
            // before you can extract the bytes from the buffer, you MUST CALL FLIP. flip() will set the limit to position and then set position to zero.
            // basically this class prepares the buffer for reading.
            buffer.flip();
            // now print as long as you have bytes in the buffer
            while(buffer.hasRemaining()) {
                System.out.print((char)buffer.get());
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
Direct vs. non-direct buffers
A byte buffer is either direct or non-direct. Given a direct byte buffer, the JVM will make its best effort to perform native I/O operations directly on it.
That is, it will attempt to avoid copying the buffer's content to (or from) an intermediate buffer before (or after) each invocation of one of the underlying operating system's native I/O operations.

A direct byte buffer may be created by invoking the allocateDirect factory method of this class.
1) The buffers returned by this method typically have somewhat higher allocation and de-allocation costs than non-direct buffers.
2) The contents of direct buffers may reside outside of the normal garbage-collected heap, and so their impact upon the memory footprint of an application might not be obvious.
3) It is recommended to use direct buffers primarily for large, long-lived buffers that are subject to the underlying system's native I/O operations.
   In general, it is best to allocate direct buffers only when they yield a measurable gain in program performance.
4) Whether a byte buffer is direct or non-direct may be determined by invoking its isDirect method.
 */

/* ChannelCopy.java next */