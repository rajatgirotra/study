package org.input_output;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

// just showing some simple methods on java.io.File class.

public class FileMethods {
    public static void main(String[] args) {
        File file = new File("org/input_output/input.txt");

        System.out.println("input.txt isFile: " + file.isFile());
        System.out.println("input.txt getAbsolutePath(): " + file.getAbsolutePath());
        System.out.println("input.txt exists: " + file.exists());
        System.out.println("input.txt canRead, canWrite, canExecute" + file.canRead() + " " + file.canWrite() + " " + file.canExecute());
        System.out.println("input.txt path: " + file.getPath());
        System.out.println("input.txt parent: " + file.getParent());

        try (FileReader reader = new FileReader("FileMethods.java")) {
            // do file operations.
        } catch (FileNotFoundException e) {
            System.out.println("File does not exist");
        } catch (IOException e) {
            e.printStackTrace();
        }
        // file will be closed here automatically.
    }
}

/*
Please read PathMethods.java next
 */