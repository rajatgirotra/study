package org.input_output;

import java.io.IOException;
import java.nio.file.*;
import java.time.LocalDateTime;
import java.util.stream.Collectors;

/*
Create a directory hierarchy public/assets/icons
Write a function "generateIndexFile" to create an index.txt in each folder public, assets, icons. index.txt should have full paths and the date each item was created.
The index.txt should be recursive which means it should contain all items that are listed in the index.txt of the child.

Next make a copy of the index.txt in each sub folder.
After you've created the copies, run the generateIndexFile function again and verify that the index.txt file has the backup copies listed in their content.
 */
public class DirectoryFileChallenge {
    public static void main(String[] args) {
        Path pathStructure = Path.of("public", "assets", "icons");

        try {
            Files.createDirectories(pathStructure);
            generateIndexFile(pathStructure.getName(0));

            // for each folder, create a copy of index.txt as indexCopy.txt
            for(int i = 1; i <= pathStructure.getNameCount(); ++i) {
                Path indexFilePath = pathStructure.subpath(0, i).resolve("index.txt");
                Path indexCopyFilePath = pathStructure.subpath(0, i).resolve("indexCopy.txt");
                Files.copy(indexFilePath, indexCopyFilePath, StandardCopyOption.REPLACE_EXISTING);
            }
            generateIndexFile(pathStructure.getName(0));
        } catch(IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void generateIndexFile(Path path) {
        // generate indexFile for top folder, then recursively for each directory.
        Path indexFile = path.resolve("index.txt");
        if(Files.exists(path) && Files.isDirectory(path)) {
            try(var pathsInDir = Files.find(path, Integer.MAX_VALUE,
                    (subPath, attr) -> true)) {
                String dirContents = pathsInDir.map(Path::toAbsolutePath).map(Path::toString)
                        .collect(Collectors.joining(System.lineSeparator(), "Directory Contents:" + System.lineSeparator(),
                                System.lineSeparator() + "Generated on: " + LocalDateTime.now()));
                Files.writeString(indexFile, dirContents, StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            // now traverse the subfolders
            try(var contents = Files.list(path)) {
                contents.filter(Files::isDirectory).forEach(DirectoryFileChallenge::generateIndexFile);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }
}

/*
Please read RandomAccess.java next
 */