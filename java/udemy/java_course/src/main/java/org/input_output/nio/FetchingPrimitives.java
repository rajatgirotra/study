package org.input_output.nio;

import java.nio.ByteBuffer;

// BufferToText.java first
// a neat way to write primitive types to a ByteBuffer is to use the appropriate view for that primitive type.
// see trivial example below.
public class FetchingPrimitives {
    private static final int BSIZE = 1024; // 1024 bytes.

    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(BSIZE); // default is all zeros
//        System.out.println(buffer.limit());
        int i = 0;
        while(i < buffer.limit()) {
            if(buffer.get() != 0) {
                System.out.println("default buffer byte is NON-ZERO");
                System.exit(1);
            }
            ++i;
        }
        System.out.println("i: " + i);
        buffer.rewind();

        // write and fetch chars
        buffer.asCharBuffer().put("How are you?");
        char c;
        while((c = buffer.getChar()) != 0) {
            System.out.print(c + " ");
        }
        System.out.println();
        buffer.rewind();

        // write and fetch short
        buffer.asShortBuffer().put((short)471142);
        System.out.println("short value: " + buffer.getShort());
        buffer.rewind();

        // write and fetch int
        buffer.asIntBuffer().put(99471142);
        System.out.println("int value: " + buffer.getInt());
        buffer.rewind();

        // write and fetch long
        buffer.asLongBuffer().put(99471142);
        System.out.println("long value: " + buffer.getLong());
        buffer.rewind();

        // write and fetch float
        buffer.asFloatBuffer().put(9.9471142f);
        System.out.println("float value: " + buffer.getFloat());
        buffer.rewind();

        // write and fetch double
        buffer.asDoubleBuffer().put(9.9471142);
        System.out.println("double value: " + buffer.getDouble());
        buffer.rewind();

    }
}

// Endian.java next