package org.input_output.nio;

// 3_README.txt first

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;

/* create a binary files filled with all 'x' chars of size 128MB.
Then create two Memory mappings. one of size 1/3 starting from position 0.
The other from position 1/2 till 3/4 of the file. Lock both regions in parallel in two threads and change all 'x' to all 'o'
 */
public class LockingMappedFiles {
    private static final int FILE_SZ = 0x8FFFFFF; // 128MB

    private static FileChannel fc = null;

    public static void main(String[] args) {
        // create a binary file with all 'x' chars
        try(var raf = new RandomAccessFile("temp.bin", "rw")) {
            fc = raf.getChannel();
            var mbb = fc.map(FileChannel.MapMode.READ_WRITE, 0, FILE_SZ);
            for(var l = 0; l < FILE_SZ; ++l) {
                mbb.put((byte)'x');
            }

            new LockAndModify("first", 0, FILE_SZ/3, mbb, 'o');
            new LockAndModify("second", FILE_SZ/2, FILE_SZ/2 + FILE_SZ/4, mbb, 'O');

            // why we need wait here? because otherwise the RandomAccessFile will get closed. i.e. the FileChannel will get closed.
            // later calling FileChannel.lock() will result in ClosedChannelException
            Thread.sleep(2000);
        } catch(IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    private static final class LockAndModify extends Thread {
        private final int start;
        private final int end;
        private final ByteBuffer buffer;
        private final char ch;

        public LockAndModify(@NotNull String name, int start, int end, ByteBuffer bb, char ch) {
            super(name);
            this.start = start;
            this.end = end;
            this.ch = ch;

            bb.limit(end);
            bb.position(start);

            buffer = bb.slice();
            start();
        }

        @Override
        public void run() {
            FileLock fl = null;
            try {
                fl = fc.lock(start, end, false);
                System.out.println("Locked " + start + " to " + end);

                // perform modification
                while(buffer.position() < buffer.limit()) {
                    buffer.put((byte)ch);
                }

                assert fl != null;
                fl.release();
                System.out.println("Released " + start + " to " + end);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
