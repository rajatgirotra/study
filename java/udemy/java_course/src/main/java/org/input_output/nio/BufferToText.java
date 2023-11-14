package org.input_output.nio;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import org.apache.commons.lang3.StringUtils;


// ChannelCopy.java first
/* If you see GetChannel.java again, we extract byte by byte from ByteBuffer and then convert to char and then print.
This isn't ideal. ByteBuffer.asCharBuffer() provides a view of the buffer as a CharBuffer which has a toString() method which can print the buffer contents
to console. Let's use that.

But remember, when we write a buffer to a channel, what encoding is getting used?? The system's default encoding "file.encoring" System property.
So when must decode this buffer when we read from it. Otherwise, we won't be able to read properly.

Or we can also encode it using some encoding which can be printed like UTF-16BE.

For decoding, we will use Charset.decode(ByteBuffer) method, which returns a CharBuffer.
 */
public class BufferToText {
    private static final int BSIZE = 1024;
    public static void main(String[] args) {
        System.out.println("Default encoding is " + System.getProperty("file.encoding"));
        System.out.println("Default encoding is " + Charset.defaultCharset());
        // write something
        try(var fc = new FileOutputStream("data.txt").getChannel()) {
            fc.write(ByteBuffer.wrap("some text".getBytes()));
        } catch(IOException e) {
            throw new RuntimeException(e);
        }

        // read
        try(var fc = new FileInputStream("data.txt").getChannel()) {
            ByteBuffer buffer = ByteBuffer.allocate(BSIZE);
            fc.read(buffer);
            buffer.flip();
            System.out.println("Should print gibberish " + buffer.asCharBuffer()); // wont work

            // rewind the buffer and decode using default Charset
            buffer.rewind();
            System.out.println("Decoded using  " + Charset.defaultCharset() + ": " + Charset.defaultCharset().decode(buffer));
        } catch(IOException e) {
            throw new RuntimeException(e);
        }

        // 2nd way. encode the buffer itself when writing
        // using UTF-16BE
        try(var fc = new FileOutputStream("data.txt").getChannel()) {
            fc.write(ByteBuffer.wrap("some text in UTF-16BE encoding".getBytes("UTF-16BE")));
        } catch(IOException e) {
            throw new RuntimeException(e);
        }

        // read
        try(var fc = new FileInputStream("data.txt").getChannel()) {
            ByteBuffer buffer = ByteBuffer.allocate(BSIZE);
            fc.read(buffer);
            buffer.flip();
            System.out.println("Should print text: " + buffer.asCharBuffer());
        } catch(IOException e) {
            throw new RuntimeException(e);
        }

        // 3rd way. write a CharBuffer itself to the channel, so when you read from it, you don't need to decode.
        try(var fc = new FileOutputStream("data.txt").getChannel()) {
            ByteBuffer buffer = ByteBuffer.allocate(24); // enough for us
            buffer.asCharBuffer().put("some text");
            fc.write(buffer);
        } catch(IOException e) {
            throw new RuntimeException(e);
        }
        // read now
        try(var fc = new FileInputStream("data.txt").getChannel()) {
            ByteBuffer buffer = ByteBuffer.allocate(24); // enough for us
            buffer.clear();
            fc.read(buffer);
            buffer.flip();
            System.out.println("Read: " + buffer.asCharBuffer());

            CharBuffer cb = buffer.asCharBuffer();
//            System.out.println(StringUtils.isAsciiPrintable(cb));
            while(cb.hasRemaining()) {
                var ch = cb.get();
                if(ch >= 32 && ch < 127) {
                    System.out.println(ch);
                }
            }
        } catch(IOException e) {
            throw new RuntimeException(e);
        }

    }
}

// FetchingPrimitives.java next