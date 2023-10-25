package org.input_output;

import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Objects;

/*
Files.walkFileTree(path) will recursively visit each file and folder at the current path.
This function provides hooks/stub functions that you can run at various entry points. The entry points are:
1) Before visiting a directory
2) After visiting a directory
3) Before Visiting a file
4) Failure in visiting a file

You can create a class which implements the FileVisitor interface or the SimpleFileVisitor<Path> class
and do more things as you recursively visit a path.

The API traverses the files and folders in DFS manner.
The four functions each return the same enum type called FileVisitResult
The FileVisitResult will dictate if the API must continue, or stop or ignore certain siblings etc.
The most important reason to use this class is when you want to store some state in this visit hierarchy.
 */
public class WalkFileTree {
    public static void main(String[] args) {
        Path path = Paths.get(".");
        System.out.println("Traversing path: " + path.toAbsolutePath());

        try {
            var paths = Files.walkFileTree(path, new StatsVisitor(1));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

class StatsVisitor extends SimpleFileVisitor<Path> {
    private Path initialPath = null;
    private int initialCount = 0;

    private int printLevel = 0;

    private final Map<Path, Long> folderSizes = new LinkedHashMap<Path, Long>();

    public StatsVisitor(int printLevel) {
        this.printLevel = printLevel;
    }

    @Override
    public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
        Objects.requireNonNull(dir);
        Objects.requireNonNull(attrs);
        if (initialPath == null) {
            initialPath = dir;
            initialCount = dir.getNameCount();
        } else {
            int relativeIndex = dir.getNameCount() - initialCount;
            if (relativeIndex == 1) {
                // we are starting to traverse another set of level 1 folder hierarchies.
                // delete everything we have and start fresh.
                folderSizes.clear();
            }
            folderSizes.put(dir, 0L);
        }
        return FileVisitResult.CONTINUE;
    }

    @Override
    public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
        Objects.requireNonNull(file);
        Objects.requireNonNull(attrs);
        folderSizes.merge(file.getParent(), 0L, (o, n) -> o += attrs.size());
        return FileVisitResult.CONTINUE;
    }

    @Override
    public FileVisitResult visitFileFailed(Path file, IOException exc) throws IOException {
        Objects.requireNonNull(file);
        if (exc != null) {
            System.out.printf("Error %s visiting file %s", exc.getClass().getSimpleName(), file.getFileName());
        }
        return FileVisitResult.CONTINUE;
    }

    @Override
    public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
        Objects.requireNonNull(dir);
        if (exc != null) {
            System.out.printf("Error %s post visiting dir %s", exc.getClass().getSimpleName(), dir.getFileName());
        } else {
            if (dir.equals(initialPath)) {
                return FileVisitResult.TERMINATE;
            }
            int relativeIndex = dir.getNameCount() - initialCount;
            if (relativeIndex == 1) {
                folderSizes.forEach((key, value) -> {
                    int level = key.getNameCount() - initialCount - 1;
                    if(level < printLevel) {
                        System.out.printf("%s[%s] - %d bytes\n", " ".repeat(level),
                                key.getFileName(), value);
                    }
                });
            } else {
                var folderSize = folderSizes.get(dir);
                folderSizes.merge(dir.getParent(), 0L, (o, n) -> o += folderSize);
            }
        }
        return FileVisitResult.CONTINUE;
    }
}

/*
How to count and print the size of each folder under the given path?
Basically we have to aggregate the file size of all files in a folder and add to its parent.
Remember it's a DFS search.
Create a Map of folderName, Size.
Store the initialPath and initialCount.

Please read WalkFileTree2.java next
 */

