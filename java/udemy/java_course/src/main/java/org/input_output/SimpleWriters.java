package org.input_output;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.sql.Array;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;
import org.input_output.StudentRecord;

/*
Very trivial way of writing to a file in Java is to use the Files.write() or Files.writeString() methods.
 */
public class SimpleWriters {
    public static void main(String[] args) {
        String header = "StudentId, Country, YearOfEnrollment, Age, Gender, Major, InternshipMonth, GPA";
        Path file = Path.of("students.csv");
        try {
            Files.writeString(file, header);
            Files.writeString(file, System.lineSeparator(), StandardOpenOption.APPEND);

            List<String> records = Stream.generate(StudentRecord::getRandomStudentRecord)
                    .limit(5)
                    .map(StudentRecord::toString)
                    .toList();
//            records.forEach(System.out::println);
            Files.write(file, records, StandardOpenOption.APPEND);

            // writing using multiple Files.write()/writeString() is inefficient. Better to use a single call.
//            List<String> lines = new ArrayList<>();
//            lines.add(header);
//            lines.addAll(records);
//            Files.write(file, lines);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
