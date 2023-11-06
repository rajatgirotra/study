package org.input_output;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.regex.MatchResult;

// usage of Scanner class
public class ScannerExample {
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(new File(Paths.get("",
                "src", "main", "java", "org", "input_output", "input2.txt").toAbsolutePath().toString()))) {
//            while(scanner.hasNextLine()) {
//                System.out.println(scanner.nextLine());
//            }

            // 2nd way. Scanner allows you to tokenize the input. default delimiter for token is whitespace
//            System.out.printf("default scanner delimiter: %s%n", scanner.delimiter());
//            scanner.useDelimiter("$"); // $ means end of line. so tokenize by lines
//            scanner.tokens().forEach(System.out::println);

            // get all words that have length of 4 or more. and sort them and print them without duplicates.
            // scanner.findAll returns a Stream<MatchResult>
            scanner.findAll("[A-Za-z]{4,}")
                    .map(MatchResult::group) // will return a stream of Strings of matches
                    .distinct()
                    .sorted()
                    .forEach(System.out::println);
        } catch(FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
 Please read ScannerFixedWidth.java next.
 */