package org.input_output.nio;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

// FetchingPrimitives.java first
// by default ByteBuffer stores bytes in BigEndian format. But you can change that by using the order() function and passing
// the endianness you want
public class Endian {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.wrap(new byte[12]);
        System.out.println("Storing abcdef in ByteBuffer using Big Endian");
        buffer.asCharBuffer().put("abcdef"); // char is 2 bytes. so for big endian, high order byte is stored first
        buffer.rewind();
        System.out.print(Arrays.toString(buffer.array()));
        System.out.println();

        buffer.clear();

        System.out.println("Storing abcdef in ByteBuffer using Little Endian");
        buffer.order(ByteOrder.LITTLE_ENDIAN);
        buffer.asCharBuffer().put("abcdef"); // char is 2 bytes. so for little endian, low order byte is stored first
        buffer.rewind();
        System.out.print(Arrays.toString(buffer.array()));
        System.out.println();
    }
}

/* Next UsingBuffers.java */