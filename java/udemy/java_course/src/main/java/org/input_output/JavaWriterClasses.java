package org.input_output;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.stream.Stream;

/*
Java provides multiple classes for File Writing. common examples are FileWriter, BufferedWriter, PrintWriter.
What is the difference really? The difference is in the API's provided:

1) FileWriter uses an internal buffer which is implementation defined. BufferedWriter offcourse is buffered. PrintWriter IS NOT BUFFERED
but most implementations internally use a BufferedWriter.
2) the .flush() api defines when the buffer is actually written to disk. these writer classes can either flush() on their own when say the
buffer is full, or based on speed of disk or amount of data to flush.
3) For writing end of line, BufferedWriter provides an explicit newLine() function. For other classes, you need to manually write a new line
using write(System.lineSeparator()) function. PrintWriter provides println() function also to write to files.
PrintWriter is also good option when you want to write a fixedWidth file as it provides printf(), format() type functions which can
take format specifier
 */
public class JavaWriterClasses {
    public static void main(String[] args) {
        // using a BufferedWriter
        Path file1 = Path.of("take1.csv");
        String header = "StudentId,Country,YearOfEnrollment,Age,Gender,Major,InternshipMonth,GPA";
        int count = 0; // increment on every write and after 5 writes just pause for 2 seconds and check the file. Used to learn when flush() happens.
        try (var bufferedWriter = Files.newBufferedWriter(file1)) {
            // write header
            bufferedWriter.write(header);
            bufferedWriter.newLine();
            var studentRecords = Stream.generate(StudentRecord::getRandomStudentRecord)
                    .limit(25)
                    .toList();
            for(StudentRecord record : studentRecords) {
                bufferedWriter.write(record.toString());
                bufferedWriter.newLine();
                ++count;
                if(count % 5 == 0) {
                    Thread.sleep(2000);
                    System.out.print("."); // for me happened, only once at end of program. (Using Ctrl+Alt+Y on Windows as shortcut to reload file)
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // using a FileWriter
        Path file2 = Path.of("take2.csv");
        try (var fileWriter = new FileWriter(file2.toFile())) {
            // write header
            fileWriter.write(header);
            fileWriter.write(System.lineSeparator());
            var studentRecords = Stream.generate(StudentRecord::getRandomStudentRecord)
                    .limit(5)
                    .toList();
            for(StudentRecord record : studentRecords) {
                fileWriter.write(record.toString());
                fileWriter.write(System.lineSeparator());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // using a PrintWriter
        Path file3 = Path.of("take3.csv");
        try (var printWriter = new PrintWriter(file3.toFile())) {
            // write header
            printWriter.write(header); // doesnt explicitly writes newLine
            printWriter.write(System.lineSeparator());
            var studentRecords = Stream.generate(StudentRecord::getRandomStudentRecord)
                    .limit(5)
                    .toList();
            for(StudentRecord record : studentRecords) {
                printWriter.println(record.toString());
//                printWriter.write(System.lineSeparator());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // using a PrintWriter to write a fixedWidth file. Left justify text and right justify numeric fields.
        Path file4 = Path.of("take4.txt");
        try (var fixedWriter = new PrintWriter(file4.toFile())) {
            // write header
            fixedWriter.write(header); // doesn't explicitly writes newLine
            fixedWriter.write(System.lineSeparator());
            var studentRecords = Stream.generate(StudentRecord::getRandomStudentRecord)
                    .limit(5)
                    .toList();
            for(StudentRecord record : studentRecords) {
                fixedWriter.printf("%6d%-4s%6d%4d%-2s%-30s%-12s%6.2f%n".formatted(
                        record.getStudentId(), record.getCountry(), record.getYearOfEnrollment(),
                        record.getAge(), record.getGender(), record.getMajor(),
                        record.getInternshipMonth(), record.getGpa()
                ));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

/*
Please see FileManagement.java next
 */
