package org.input_output;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.time.ZoneId;

public class FilesListWalkFind {
    public static void main(String[] args) {
        // get current working directory
        Path path = Path.of("");
        System.out.println("cwd = " + path.toAbsolutePath());

        /* The Stream<Path> returned by Files.list() encapsulates a DirectoryStream.
        Closing a DirectoryStream releases any resources associated with the stream. Failure to close the stream may
        result in a resource leak. The try-with-resources statement provides a useful construct to ensure that the stream is closed.

        same with walk and find methods of Files class.
         */
        try (var paths = Files.list(path)) {
            paths.map(FilesListWalkFind::listDir)
                    .forEach(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        System.out.println("=".repeat(50));

        try (var paths = Files.walk(path, 2)) {
            paths.filter(Files::isRegularFile)
                    .map(FilesListWalkFind::listDir)
                    .forEach(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        System.out.println("=".repeat(50));
        try (var paths = Files.find(path, Integer.MAX_VALUE,
                (p, attr) -> attr.isRegularFile() && attr.size() > 300)) {
            paths.map(FilesListWalkFind::listDir)
                    .forEach(System.out::println);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        System.out.println("============= DirectoryStream ================");
        try(var ds = Files.newDirectoryStream(path)) {
            ds.forEach(d -> System.out.println(FilesListWalkFind.listDir(d)));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        System.out.println("============= DirectoryStream ================");
        try(var ds = Files.newDirectoryStream(path,
                Files::isRegularFile)) {
            ds.forEach(d -> System.out.println(FilesListWalkFind.listDir(d)));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }


    }

    private static String listDir(Path path) {
        try {
            // is path a directory
            boolean isDir = Files.isDirectory(path);
            var fileTime = Files.getLastModifiedTime(path);
            LocalDateTime modDT = LocalDateTime.ofInstant(fileTime.toInstant(), ZoneId.systemDefault());
            var sz = Files.size(path);
            return "%tD %tT %-5s %12s %s".formatted(modDT, modDT, isDir ? "<DIR>": "",
                    isDir ? "" : sz, path);
        } catch(IOException e) {
            System.out.println("Oops! Something went wrong in listDir method");
            return path.toString();
        }
    }
}

/*
Please read WalkFileTree.java next
 */