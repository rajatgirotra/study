package org.input_output.nio;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;

// read Endian.java first
/*
create a ByteBuffer with value = "UsingBuffers". Then
1) print it out
2) swap each pair of characters and print again (sUniBgfuefsr)
3) then swap again and print. (UsingBuffers)
 */
public class UsingBuffers {
    public static void main(String[] args) {
        String str = "UsingBuffers";
        ByteBuffer bb = ByteBuffer.allocate(str.length() * 2); // because character is two bytes
        bb.asCharBuffer().put(str.toCharArray());

        System.out.println(bb.asCharBuffer());
        swapAdjacent(bb);
        System.out.println(bb.asCharBuffer());
        swapAdjacent(bb);
        System.out.println(bb.asCharBuffer());
    }

    private static void swapAdjacent(ByteBuffer bb) {
        CharBuffer cb = bb.asCharBuffer();
        while(cb.hasRemaining()) {
            cb.mark();
            var c1 = cb.get();
            var c2 = cb.get();
            cb.reset();
            cb.put(c2); cb.put(c1);
        }
    }
}

/* 2_README.txt next */