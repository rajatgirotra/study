package org.input_output;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

/* read a text file.
tokenize and read its words. Ignore any punctuation.
ignore words of 4 or fewer characters.
count the occurrence of each word
print the top 10 words
 */
public class FileReadChallenge {
    public static void main(String[] args) {
        var fileName = Paths.get("", "src", "main", "java", "org", "input_output", "article.txt").toAbsolutePath();
        var excluded = List.of("their", "after");

        try (BufferedReader reader = new BufferedReader(new FileReader(fileName.toString()))) {
            Pattern pattern = Pattern.compile("\\p{javaWhitespace}+");
            // print number of lines.
//            System.out.printf("%d lines in file", reader.lines().count());

            //print words in file
//            System.out.printf("%d words in file", reader.lines().flatMap(pattern::splitAsStream).count());

            //print words in file (another way)
//            System.out.printf("%d words in file", reader.lines()
//                    .flatMap(l -> Arrays.stream(l.split(pattern.toString()))).count());

            //print words in file (yet another way)
//            System.out.printf("%d words in file", reader.lines()
//                    .mapToLong(l -> l.split(pattern.toString()).length).sum());

            // now do the actual task
            var result = reader.lines()
                    .flatMap(pattern::splitAsStream) // returns Stream<String>
                    .map(s -> s.replaceAll("\\p{Punct}+", "")) // replace all punctuation
                    .filter(s -> s.length() > 4) // get words greater than 5 chars
                    .map(String::toLowerCase) // convert all to lower case
                    .filter(s -> !excluded.contains(s))
                    .collect(Collectors.groupingBy(s -> s, Collectors.counting()));

            // now get only top 10 occurrences
            result.entrySet().stream()
                    .sorted(Comparator.comparing(Map.Entry::getValue, Comparator.reverseOrder()))
                    .limit(10)
                    .forEach(item -> System.out.println(item.getKey() + " - " + item.getValue() + " times"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Now same as above but without using streams
        System.out.println("-".repeat(20));
        try {
            Pattern pattern = Pattern.compile("\\w{5,}"); // words of 5 or more characters
            var lines = Files.readString(fileName);
            lines.replaceAll("\\p{Punct}+", ""); // replace all punctuations
            Map<String, Long> m = new HashMap<>(); // word to word count map
            Matcher matcher = pattern.matcher(lines);
            while(matcher.find()) {
                String word = matcher.group().toLowerCase();
                if(!excluded.contains(word)) {
                    m.merge(word, 1L, (o, n) -> o += n);
                }
            }

            // sort and get top 10 entries
            var sortedEntries = new ArrayList<>(m.entrySet());
            sortedEntries.sort(Comparator.comparing(Map.Entry::getValue, Comparator.reverseOrder()));
            for(int i = 0; i < Math.min(10, sortedEntries.size()); ++i) {
                var item = sortedEntries.get(i);
                System.out.println(item.getKey() + " - " + item.getValue() + " times");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

/*
Please read SimpleWriters.java next
 */