package org.input_output.nio;

/* GetChannel.java first */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;

// very trivial class to copy one file to another
public class ChannelCopy {
    private static final int BSIZE = 1024;
    public static void main(String[] args) {
        if(args.length != 2) {
            System.out.println("arguments: sourcefile destfile");
            System.exit(1);
        }

        try(var inFC = new FileInputStream(args[0]).getChannel();
        var outFC = new FileOutputStream(args[1]).getChannel()) {
            ByteBuffer buffer = ByteBuffer.allocate(BSIZE);
            while(inFC.read(buffer) != -1) {
                buffer.flip(); // prepare buffer for extracting bytes
                outFC.write(buffer);
                buffer.clear(); // clear buffer again to be used again for reading from a channel.
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
However there is much better transferTo() and transferFrom() methods available on FileChannel to copy a file.
or even Files.copy()

BufferToText.java next
 */