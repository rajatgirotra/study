package org.input_output;

import org.w3c.dom.ls.LSOutput;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.TreeMap;

/* Read an employee.dat file. it contains an index + employee data.
Layout of file is:
<RECORD_COUNT> followed by key value pairs of employee id and file pointer of the employee record in the file. Both are long fields.
Fetch record for a given employee id and update its salary in the file. read the employee record again from file and validate that salary is updated.
Employee record format is:
EmployeeId, int
Salary: double
FirstName: String
LastName: String
 */
public class EmployeeRecords {

    public static void main(String[] args) {
        Path path = Path.of("employees.dat");
        if(!Files.isRegularFile(path)) {
            System.out.println("Unable to find file employees.dat for reading");
            return;
        }

        var index = loadIndex(path);

        // access/modify random employee. We know the employee Id's from the console output
        int employeeId = 999;
        modifyRecord(path, employeeId, index);
        printRecord(path, employeeId, index);

    }

    private static Map<Integer, Long> loadIndex(Path raFile) {
        Map<Integer, Long> index = new TreeMap<>();
        try(var randomAccessFile = new RandomAccessFile(raFile.toString(), "r")) {
            int recCount = randomAccessFile.readInt();
            System.out.printf("Loading %s index records%n", recCount);
            for(int i = 0; i < recCount; ++i) {
                int key = randomAccessFile.readInt();
                long value = randomAccessFile.readLong();
//                System.out.println(key + " -> " + value);
                index.put(key, value);
            }
            System.out.println("Employee Ids loaded are:");
            index.forEach((k, v) -> {
                System.out.println(k);
            });
            return index;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void modifyRecord(Path raFile, int employeeId, Map<Integer, Long> index) {
        try(var randomAccessFile = new RandomAccessFile(raFile.toString(), "rw")) {
            randomAccessFile.seek(index.get(employeeId));
            int id = randomAccessFile.readInt();
            long salaryPos = randomAccessFile.getFilePointer();
            double salary = randomAccessFile.readDouble();
            String firstname = randomAccessFile.readUTF();
            String lastname = randomAccessFile.readUTF();
            EmployeeRecord record = new EmployeeRecord(id, salary, firstname, lastname);
            System.out.println("Original Record: " + record);
            salary += 100;
            randomAccessFile.seek(salaryPos);
            randomAccessFile.writeDouble(salary);
            System.out.println("Modified salary to: " + salary);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void printRecord(Path raFile, int employeeId, Map<Integer, Long> index) {
        try(var randomAccessFile = new RandomAccessFile(raFile.toString(), "r")) {
            randomAccessFile.seek(index.get(employeeId));
            int id = randomAccessFile.readInt();
            long salaryPos = randomAccessFile.getFilePointer();
            double salary = randomAccessFile.readDouble();
            String firstname = randomAccessFile.readUTF();
            String lastname = randomAccessFile.readUTF();
            EmployeeRecord record = new EmployeeRecord(id, salary, firstname, lastname);
            System.out.println("Printing Record: " + record);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

}

/*
PrimitiveSerialization.java next
 */