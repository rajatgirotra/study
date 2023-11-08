package org.input_output;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

/*  to recursive copy and recursive delete, you have to manually write some code

 */
public class RecursiveCopyDelete {
    public static void main(String[] args) {
        Path source = Path.of("", "target", "maven-status");
        Path target = Path.of("", "target", "copy");

        try {
//            Files.deleteIfExists(target); // this throws a DirectoryNotEmptyException
            recursiveDelete(target);
            recursiveCopy(source, target);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // running this program second time will result in FileAlreadyExistsException.
    // so we also need a recursiveDelete function
    private static void recursiveCopy(Path source, Path target) throws IOException {
        // This can throw DirectoryNotEmptyException if this folder already exists.
        Files.copy(source, target, StandardCopyOption.REPLACE_EXISTING); // overwrite
        // recursively copy files and folders
        if (Files.isDirectory(source)) {
            try (var contents = Files.list(source)) {
                contents.toList().forEach(p -> {
                    try {
                        RecursiveCopyDelete.recursiveCopy(p, target.resolve(p.getFileName()));
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                });
            }
        }
    }
    private static void recursiveDelete(Path target) throws IOException {
        if(Files.isDirectory(target)) {
            // recursively call
            try(var contents = Files.list(target)) {
                contents.toList().forEach(p -> {
                    try {
                        recursiveDelete(p);
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                });
            }
        }
        Files.deleteIfExists(target);
    }
}

/* There is also a function called Reader.transferTo(Writer) which basically opens a file and copies the contents to a destination.
But the above method is preferred. You can use transferTo when may be you are reading data over a network or URL and need to write
it to local disk. or you want to transform the data before writing.

See TransferToUsage.java next
 */