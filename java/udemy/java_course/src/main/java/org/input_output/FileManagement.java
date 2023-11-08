package org.input_output;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class FileManagement {
    public static void main(String[] args) {
        // you can rename(move files) using File.rename() method. However it only returns a boolean
        // and when it fails (returns false), you don't have much insight into what went wrong.

//        File oldFile = new File("input.txt"); // relative path. When running via Intellij, check your working directory in Configuration.
//        File newFile = new File("input.txt");
//
//        if(oldFile.exists()) {
//            var result = oldFile.renameTo(newFile);
//            if(result) {
//                System.out.println("File renamed successfully!");
//            } else {
//                System.out.println("failed to rename File!!");
//            }
//        } else {
//            System.out.println("File does not exist!!");
//        }

        // instead prefer using Files.move(Path old, Path new) instead which throws an exception on failure
        Path oldPath = Path.of("input.txt");
        Path newPath = Path.of("files/input.txt");
        try {
            // note that you can't create directories when moving. Make sure destination directory exist before moving
//            Files.createDirectories(newPath.subpath(0, newPath.getNameCount()-1));
//            Files.move(oldPath, newPath);
//            System.out.printf("%s renamed (moved to) -> %s".formatted(oldPath, newPath));

            // Similarly we have File.copy() --> However, it only performs a shallow copy. i.e. it doesnt copy any files or folders inside it.
            Path oldDir = Path.of("files");
            Path newDir = Path.of("resources");
            Files.copy(oldDir, newDir);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

/*
Please read RecursiveCopyDelete.java next
 */
