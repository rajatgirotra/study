package org.input_output;

import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.*;

/* same as WalkFileTree.java but we want to find the folder size + count of files + count of sub-folders and report it

 */
public class WalkFileTree2 {
    public static void main(String[] args) {
        Path path = Paths.get("..");
        System.out.println("Traversing path: " + path.toAbsolutePath());

        try {
            var paths = Files.walkFileTree(path, new StatsVisitor2(3));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

class StatsVisitor2 extends SimpleFileVisitor<Path> {
    private Path initialPath = null;
    private int initialCount = 0;

    private int printLevel = 0;

    private final Map<Path, Map<String, Long>> folderSizes = new LinkedHashMap<>();

    private static final String DIR_COUNT = "DirCount";
    private static final String FILE_COUNT = "FileCount";
    private static final String FILE_SZ = "FileSize";

    public StatsVisitor2(int printLevel) {
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
            folderSizes.put(dir, new HashMap<>());
        }
        return FileVisitResult.CONTINUE;
    }

    @Override
    public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
        Objects.requireNonNull(file);
        Objects.requireNonNull(attrs);
        // add size of this file to its parents FILE_SIZE
        // add 1 to this file's parent FILE_COUNT

        //get the parent first
        var parentMap = folderSizes.get(file.getParent());
        if(parentMap != null) {
            var fileSize = attrs.size();
            parentMap.merge(FILE_SZ, fileSize, (o, n) -> o += n);
            parentMap.merge(FILE_COUNT, 1L, Math::addExact);
        }
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
                       var sz = value.getOrDefault(FILE_SZ, 0L);
                        System.out.printf("%s[%s] - %d bytes, %d files, %d folders%n",
                                " ".repeat(level), key.getFileName(), sz, value.getOrDefault(FILE_COUNT, 0L),
                                value.getOrDefault(DIR_COUNT, 0L));
                    }
                });
            } else {
                // get this dir's map
                var thisDirMap = folderSizes.get(dir);
                // get the parents map
                var parentMap = folderSizes.get(dir.getParent());

                // get this dirs folder and file size
                var fileCount = thisDirMap.getOrDefault(FILE_COUNT, 0L);
                // get this dirs folder count
                var dirCount = thisDirMap.getOrDefault(DIR_COUNT, 0L);
                var fileSz = thisDirMap.getOrDefault(FILE_SZ, 0L);

                parentMap.merge(FILE_COUNT, fileCount, Math::addExact);
                parentMap.merge(FILE_SZ, fileSz, Math::addExact);
                parentMap.merge(DIR_COUNT, dirCount + 1, (o, n) -> o += n);
            }
        }
        return FileVisitResult.CONTINUE;
    }
}

/*
Please see 2_README.txt next
 */

