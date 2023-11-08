package org.input_output;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/*
RandomAccessFile in java provides you a file pointer using which you can seek() to any position in a file and start reading bytes from that offset.
Usually for to create RandomAccess file, you will create an index for that file which tells you which record is at which file offset.

You can store records of fixed width or variable width, both. If you look at RandomAccessFile JDK 11 doc, you will see it provides to read and write all primitive types,
string and other objects. Note that readUTF() and writeUTF() are very special. They are used to read and write variable length strings. You only need these methods and internally,
Java will keep track of the size of the string that needs to be read or written.

We have students.json file in this folder, which has 1000 records. We want to create a RandomAccessFile to access records based on studentId.
We will create an index for the RandomAccessFile we create. The index can be part of the file itself or stored as a separate file.
We will do both. First will create one file which contains the index also, then will create 2 files - one for index and one for data.

Layout of single file.
1) 4 byte integer for count of records in the file
2) space for 8 byte studentId + 8 byte file offset of the record. (total for 1000 records)
3) Actual records start.
 */
public class RandomAccess {
    private static final Map<Long, Long> indexedIds = new TreeMap<>();
    private static int recordCount = 0;

    public static void main(String[] args) {
        // We will create the RandomAccessFile in 2 steps. 1st step we will write the records and in 2nd step we will write the index starting at position 0 in file.

        // create a function which takes Path of students.json as argument and creates a List<String> of records.
        // create a function which takes a List<String> of records and a RandomAccessFile name.
        // Iterate the file and create a map<StudentID, filePosition> this should be a LinkedHashMap<>, assume all studentId's are in sequence. Return this Map.
        // we want to iterate the Map in sorted order of studentId's when we create the index.
        try {
            Path p = Path.of("students.json");
            var studentRecords = parseStudentRecords(p);

            Path datFileName = Path.of("students.dat");
            Files.deleteIfExists(datFileName);

            // step 1.
            writeRecordsToFile(datFileName, studentRecords);

            // step 2.
            writeIndexToFile(datFileName);

            // now create a scanner to read student id from console and lookup in the dat file
            // ideally the reading would happen in a separate process, so first you should read the index and load it in map. However, we skip it here as it is trivial.
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter studentId to lookup: ");
            while(scanner.hasNext()) {
                long studentId = Long.parseLong(scanner.nextLine());
                if(studentId < 1) {
                    break;
                }
                findAndPrintStudentId(studentId, datFileName);
                System.out.print("Enter next studentId to lookup: ");
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static List<String> parseStudentRecords(Path jsonFile) throws IOException {
        String contents = Files.readString(jsonFile);
        // remove the first [ and the last ] from the file.
        contents = contents.replaceFirst("^(\\[)", "").replaceFirst("(\\])$", "");
        var records = contents.split(System.lineSeparator());
        recordCount = records.length;
        System.out.println("# of records: " + records.length);
        return List.of(records);
    }

    public static void writeRecordsToFile(Path raFile, List<String> records) {
        // a pattern to extract studentId from a json record.
        Pattern pattern = Pattern.compile("studentId\":([0-9]+)");

        try (var randomAccessFile = new RandomAccessFile(raFile.toString(), "rw")) {
            randomAccessFile.seek(4 + (16L * recordCount));
            for (String record : records) {
                Matcher m = pattern.matcher(record);
                if (m.find()) {
                    long studentId = Long.parseLong(m.group(1));
                    indexedIds.put(studentId, randomAccessFile.getFilePointer());
                    // write the record now
                    randomAccessFile.writeUTF(record);
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void writeIndexToFile(Path raFile) {
        try (var randomAccessFile = new RandomAccessFile(raFile.toString(), "rw")) {
            randomAccessFile.seek(0);
//            randomAccessFile.writeInt(recordCount); recordCount will be incorrect here. as incorrect studentIds may be skipped.
            randomAccessFile.writeInt(indexedIds.size());
            for(var entry : indexedIds.entrySet()) {
                randomAccessFile.writeLong(entry.getKey());
                randomAccessFile.writeLong(entry.getValue());
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void findAndPrintStudentId(long studentId, Path datFilePath) {
        try(var randomAccessFile = new RandomAccessFile(datFilePath.toString(), "r")) {
            int recordsInDatFile = randomAccessFile.readInt();
            if(indexedIds.containsKey(studentId)) {
                randomAccessFile.seek(indexedIds.get(studentId));
                System.out.println("Record Found: " + randomAccessFile.readUTF());
            } else {
                System.out.println("StudentId " + studentId + " not found!");
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}