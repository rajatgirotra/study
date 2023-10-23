package org.input_output;

/* Just showing some Paths, Path, Files APIs */

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.SQLOutput;
import java.time.Instant;

public class PathMethods {
    public static void main(String[] args) {
        // filename
        String filename = "inputfile.txt";
        String pathname = "inputpath.txt";
        usefile(filename);
        usepath(pathname);
        printinfo(pathname);
    }

    private static void usefile(String filename) {
        System.out.println("=".repeat(50));
        File file = new File(filename);

        // if file exists, delete it first
        boolean fileExists = file.exists();
        System.out.printf("file exists [%s]: %b\n", filename, fileExists);
        if (fileExists) {
            fileExists = !file.delete();
            if(!fileExists) {
                System.out.printf("deleted file [%s]\n" , filename);
            } else {
                System.out.printf("error deleting file [%s]\n" , filename);
                return;
            }
       }

        // create new file
        try {
            boolean created = file.createNewFile();
            if(created) {
                System.out.printf("New file created [%s]\n" , file.getPath());
            } else {
                System.out.printf("failed to create new file [%s]\n", file.getPath());
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        System.out.printf("inputfile.txt canWrite: %b\n", file.canWrite());
    }

    private static void usepath(String filename) {
        System.out.println("=".repeat(50));
        Path path = Paths.get(filename);

        // if file exists, delete it first
        boolean fileExists = Files.exists(path);
        System.out.printf("file exists [%s]: %b\n", filename, fileExists);
        if (fileExists) {
            try {
                Files.delete(path);
                System.out.printf("deleted file [%s]\n" , filename);
            } catch (IOException e) {
                System.out.println("Something went wrong trying to delete file " + filename);
            }
        }

        // create new file
        try {
            Files.createFile(path);
            System.out.printf("New file created [%s]\n" , path);
        } catch (IOException e) {
            System.out.printf("failed to create new file [%s]\n", path);
            e.printStackTrace();
        }
        System.out.printf("inputfile.txt canWrite: %b\n", Files.isWritable(path));

        // write to file
        System.out.println("Writing to file");
        try {
            Files.writeString(path, """
                    Hello world
                    from a 
                    sample app.
                    """);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // read from file now
        System.out.println("Reading from file(line by line)");
        try {
            var lines = Files.readAllLines(path);
            lines.forEach(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        System.out.println("=".repeat(50));
    }

    private static void printinfo(String filename) {
        Path path = Paths.get(filename);
        System.out.println("=".repeat(50));
        System.out.println("Printing path info");
        System.out.println("filename: " + path.getFileName());
        System.out.println("parent: " + path.getParent());
        System.out.println("absolute path: " + path.toAbsolutePath());
        System.out.println("path is absolute: " + path.isAbsolute());
        System.out.println("path root: " + path.getRoot());
        System.out.println("path root on absolute path: " + path.toAbsolutePath().getRoot());

        // print paths step by step.
        System.out.println("Printing path step by step using Path.getName(i)");
        var absolutePath = path.toAbsolutePath();
        int i = 0;
        for(i = 0; i < absolutePath.getNameCount(); ++i) {
            System.out.println(".".repeat(i) + absolutePath.getName(i));
        }

        System.out.println("Printing path step by step using Path.iterator()");
        i = 0;
        for (Path value : absolutePath) {
            System.out.println(".".repeat(i) + value);
            ++i;
        }

        // create directory
        String newFile = "files/input.txt";
        Path newFilePath = Paths.get(newFile);
        try {
            if(!Files.exists(newFilePath.getParent()))
                Files.createDirectory(newFilePath.getParent());

            Files.delete(newFilePath);
            Files.createFile(newFilePath);
            // write something to file.
            Files.writeString(newFilePath, Instant.now() + " Hello World\n");

            var attr = Files.readAttributes(newFilePath, "*"); // attr is a Map
            System.out.println("File attributes are");
            attr.entrySet().forEach(System.out::println);

            System.out.println("Content type: " + Files.probeContentType(newFilePath));

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

/*
Please read FilesListWalkFind.java next
 */
