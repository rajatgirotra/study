package org.input_output;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Set;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

// how to use Files class for reading text files.
public class FilesRead {
    public static void main(String[] args) {
        // First lets print how to get the default character set encoding.
        System.out.println(System.getProperty("file.encoding"));
        System.out.println(Charset.defaultCharset());

        // read a file using Files.readAllBytes
        var fileName = Paths.get("", "src", "main", "java", "org", "input_output", "fixedWidth.txt")
                .toAbsolutePath();

        try {
            // readAllBytes returns a byte array byte[]
            String content = new String(Files.readAllBytes(fileName));
            System.out.println(content);
            System.out.println("-----------------");
            // readString returns a String
            System.out.println(Files.readString(fileName));

            // get the distinct departments again without using Streams
            // readAllLines returns a List<String>
            Set<String> depts = new TreeSet<>();
            Pattern p = Pattern.compile("(.{15})(.{3})(.{12})(.{8})(.{2}).*");
            Files.readAllLines(fileName).forEach(line -> {
                if (!line.startsWith("Name")) {
                    var result = p.matcher(line);
                    if (result.matches()) {
                        depts.add(result.group(3).trim());
                    }
                }
            });
            System.out.println(depts);

            // another way using streams.
            // lines returns a Stream<String>
            try (var stringStream = Files.lines(fileName)) {
                var result = stringStream.skip(1) // skip first row
                        .map(p::matcher)
                        .filter(Matcher::matches)
                        .map(m -> m.group(3).trim())
                        .distinct()
                        .sorted()
                        .toArray(String[]::new);
                System.out.println(Arrays.toString(result));
            }

            // get count of employees in each department
            try (var stringStream = Files.lines(fileName)) {
                var result = stringStream.skip(1) // skip first row
                        .map(p::matcher)
                        .filter(Matcher::matches)
                        .collect(Collectors.groupingBy(
                                m -> m.group(3).trim(), Collectors.counting()));
                result.entrySet().forEach(System.out::println);
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
FileReadChallenge.java next
 */
