package org.input_output;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

// simple use of FileReader class. Note that FileReader reads characters. Internally it uses a buffer but the buffer size
// is implementation dependant.
public class SimpleFileReader {
    public static void main(String[] args) {
//        try (FileReader reader = new FileReader(Paths.get("",
//                "src", "main", "java", "org", "input_output", "input.txt").toAbsolutePath().toString())) {
//            int data = 0;
//            while((data = reader.read()) != -1) {
////                System.out.println(data);
//                System.out.println((char)data); // but how many disk reads have taken place?? for that lets read into a character array
//            }
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }

//        try (FileReader reader = new FileReader(Paths.get("",
//                "src", "main", "java", "org", "input_output", "input.txt").toAbsolutePath().toString())) {
//            char[] block = new char[1000];
//            int data = 0;
//            while((data = reader.read(block, 0, block.length)) != -1) {
//                String content = new String(block, 0, data);
//                System.out.printf("[%d] bytes -> %s", data, content); // just one disk read.
//            }
//        } catch (IOException e) {
//            throw new RuntimeException(e);
//        }

        try (BufferedReader reader = new BufferedReader(new FileReader(Paths.get("",
                "src", "main", "java", "org", "input_output", "input2.txt").toAbsolutePath().toString()))) {

            // BufferedReader allows you to also read line by line
            reader.lines().forEach(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
Please read ScannerExample.java next.
 */