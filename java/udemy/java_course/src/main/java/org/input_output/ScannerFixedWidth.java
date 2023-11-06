package org.input_output;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Scanner;
import java.util.regex.MatchResult;

public class ScannerFixedWidth {
    public static void main(String[] args) {
        // fixedWith column size are 15, 3, 12, 8, 2
        try (Scanner scanner = new Scanner(new File(Paths.get("",
                "src", "main", "java", "org", "input_output", "fixedWidth.txt").toAbsolutePath().toString()))) {

            // get the distinct states in an array and print it.
            // get the distinct department in an array and print it.
            var results = scanner.findAll("(.{15})(.{3})(.{12})(.{8})(.{2}).*")
                    .skip(1) // skip the first header row
//                    .map(m -> m.group(5)) // group 5 is states
                    .map(m -> m.group(3).trim()) // group 5 is states
                    .distinct()
                    .sorted()
                    .toArray(String[]::new);
            System.out.println(Arrays.asList(results));
        } catch(FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
