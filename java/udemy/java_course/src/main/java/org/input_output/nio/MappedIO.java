package org.input_output.nio;

import java.io.*;
import java.nio.IntBuffer;
import java.nio.channels.FileChannel;
import java.util.Map;

public class MappedIO {
    private final static int numOfInts = 4_000_000;
    private final static int numOfUbuffInts = 200_000;

    private abstract static class Tester {
        private String name;

        public Tester(String name) {
            this.name = name;
        }

        public void runTest() {
            System.out.print("Test: " + name);
            var startNanos = System.nanoTime();
            try {
                test();
                var endNanos = System.nanoTime();
                System.out.println(", duration: " + (endNanos - startNanos));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

        }

        public abstract void test() throws IOException;
    }

    private static Tester[] tests = {
            // write numOfInts integers to file
            new Tester("Stream Write") {
                @Override
                public void test() throws IOException {
                    try (DataOutputStream dos = new DataOutputStream(new BufferedOutputStream(
                            new FileOutputStream(new File("temp.dat"))))) {
                        for (int i = 0; i < numOfInts; ++i) {
                            dos.writeInt(i);
                        }
                    }
                }
            },
            // write numOfInts integers to file
            new Tester("Mapped Write") {
                @Override
                public void test() throws IOException {
                    try (var raf = new RandomAccessFile("temp.dat", "rw")) {
                        FileChannel fc = raf.getChannel();
                        var intBuffer = fc.map(FileChannel.MapMode.READ_WRITE, 0, fc.size()).asIntBuffer();
                        for (int i = 0; i < numOfInts; ++i) {
                            intBuffer.put(i);
                        }
                    }
                }
            },
            // read numOfInts integers to file
            new Tester("Stream Read") {
                @Override
                public void test() throws IOException {
                    try (DataInputStream dis = new DataInputStream(new BufferedInputStream(
                            new FileInputStream(new File("temp.dat"))))) {
                        for (int i = 0; i < numOfInts; ++i) {
                            dis.readInt();
                        }
                    }
                }
            },
            // read numOfInts integers to file
            new Tester("Mapped Read") {
                @Override
                public void test() throws IOException {
                    try (var raf = new RandomAccessFile("temp.dat", "r")) {
                        FileChannel fc = raf.getChannel();
                        var intBuffer = fc.map(FileChannel.MapMode.READ_ONLY, 0, fc.size()).asIntBuffer();
                        while (intBuffer.hasRemaining()) {
                            intBuffer.get();
                        }
                    }
                }
            },

            // read and write numOfInts integers to file
            new Tester("Stream Read/Write") {
                @Override
                public void test() throws IOException {
                    try (var raf = new RandomAccessFile("temp.dat", "rw")) {
                        raf.writeInt(1);
                        for (int i = 1; i < numOfUbuffInts; ++i) {
                            raf.seek(raf.length() - 4);
                            raf.writeInt(raf.readInt());
                        }
                    }
                }
            },

            // read and write numOfInts integers to file
            new Tester("Mapped Read/Write") {
                @Override
                public void test() throws IOException {
                    try (var raf = new RandomAccessFile("temp.dat", "rw")) {
                        FileChannel fc = raf.getChannel();
                        IntBuffer intBuffer = fc.map(FileChannel.MapMode.READ_WRITE, 0, fc.size()).asIntBuffer();
                        intBuffer.put(1);
                        for (int i = 1; i < numOfUbuffInts; ++i) {
                            intBuffer.put(intBuffer.get(i - 1));
                        }
                    }
                }
            }
    };

    public static void main(String[] args) {
        for (Tester test : tests) {
            test.runTest();
        }
    }
}

/* As you can see from output, MappedByteBuffer are significantly faster. */
// 3_README.txt