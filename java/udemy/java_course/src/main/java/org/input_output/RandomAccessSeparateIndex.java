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
Same as RandomAccess.java except that index is separately stored.
 */
public class RandomAccessSeparateIndex {
    private static final Map<Long, Long> indexedIds = new TreeMap<>();
    private static int recordCount = 0;

    public static void main(String[] args) {
        try {
            Path p = Path.of("students.json");
            var studentRecords = parseStudentRecords(p);

            Path idxFileName = Path.of("students.idx");
            Path binFileName = Path.of("students.bin");
            Files.deleteIfExists(idxFileName);
            Files.deleteIfExists(binFileName);

            // step 1.
            writeRecordsToFile(binFileName, studentRecords);

            // step 2.
            writeIndexToFile(idxFileName);

            // now create a scanner to read student id from console and lookup in the dat file
            // loadIndex first
            var index = loadIndex(idxFileName);
            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter studentId to lookup: ");
            while(scanner.hasNext()) {
                long studentId = Long.parseLong(scanner.nextLine());
                if(studentId < 1) {
                    break;
                }
                findAndPrintStudentId(studentId, binFileName, index);
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
            randomAccessFile.seek(0); // start at beginning of the file.
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
            randomAccessFile.writeInt(indexedIds.size());
            for(var entry : indexedIds.entrySet()) {
                randomAccessFile.writeLong(entry.getKey());
                randomAccessFile.writeLong(entry.getValue());
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static Map<Long, Long> loadIndex(Path raFile) {
        Map<Long, Long> index = new HashMap<>();
        try(var randomAccessFile = new RandomAccessFile(raFile.toString(), "r")) {
            int recCount = randomAccessFile.readInt();
            System.out.println("# of index entries read: " + recCount);
            for(int i = 0; i < recCount; ++i) {
                index.put(randomAccessFile.readLong(), randomAccessFile.readLong());
            }
            return index;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void findAndPrintStudentId(long studentId, Path binFilePath, Map<Long, Long> index) {
        try(var randomAccessFile = new RandomAccessFile(binFilePath.toString(), "r")) {
            if(index.containsKey(studentId)) {
                randomAccessFile.seek(index.get(studentId));
                System.out.println("Record Found: " + randomAccessFile.readUTF());
            } else {
                System.out.println("StudentId " + studentId + " not found!");
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
please read EmployeeRecords.java next
 */