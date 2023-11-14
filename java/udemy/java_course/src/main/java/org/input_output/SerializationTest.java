package org.input_output;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class SerializationTest {
    public static void main(String[] args) {
        Path file = Path.of("dummyrecord.dat");
        DummyRecord record = new DummyRecord(5555,"Rajat", 88888, List.of("A", "B", "C"));
//        writeDummyRecord(file, record);
        readDummyRecord(file);

        Path file2 = Path.of("dummyrecord2.dat");
        DummyRecord record2 = new DummyRecord(6666,"Vidhu", 22222, List.of("A", "B", "C"));
        writeDummyRecord(file2, record2);
        readDummyRecord(file2);
    }

    private static void writeDummyRecord(Path file, DummyRecord record) {
        System.out.println("Writing DummyRecord to file: " + record);

        try(var outputStream = new ObjectOutputStream(Files.newOutputStream(file))) {
            outputStream.writeObject(record);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void readDummyRecord(Path file) {
        try(var inputStream = new ObjectInputStream(Files.newInputStream(file))) {
            DummyRecord record = (DummyRecord)inputStream.readObject();
            System.out.println("Reading DummyRecord from file: " + record);
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
