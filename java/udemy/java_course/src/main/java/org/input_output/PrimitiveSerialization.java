package org.input_output;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

/*
Java provides a DataOutputStream and DataInputStream class used for primitive serialization and de-serialization. It is very trivial.

For object serialization, java provides ObjectOutputStream and ObjectInputStream class. However, to use these classes, your class must implement the
Serializable interface in java.io package.

What actually gets stored when an object is serialized?
The default serialization mechanism will store
1) the class of the object
2) the class signature (like access modifier of the class, its method names and return types etc.)
3) values of all the non-transient and non-static fields.
4) If object has references to other objects, those objects too are written (given that they too implement Serializable).
 Multiple references to a single object are encoded using a reference sharing mechanism so that graphs of objects can be restored to the same shape during serialization.
 */
public class PrimitiveSerialization {
    public static void main(String[] args) {
        Path primitives = Path.of("primitives.dat");
        writePrimitives(primitives);
        readPrimitives(primitives);

        Path playerFile = Path.of("player.dat");
        Player player = new Player("Rajat", 88888);
        writePlayer(playerFile, player);
        readPlayer(playerFile);
    }

    private static void writePrimitives(Path fileName) {
        try(var dataStream = new DataOutputStream(
                new BufferedOutputStream(
                        new FileOutputStream(fileName.toFile())))) {

            int myInt = 88;
            long myLong = 1_999_999_999L;
            boolean myBoolean = true;
            char myChar = 'R';
            float myFloat = 21.5f;
            double myDouble = 99.75;
            String myString = "Hello World";

            long position = 0;

            dataStream.writeInt(myInt);
            System.out.println("myInt writes " + (dataStream.size() - position) + " bytes.");
            position = dataStream.size();

            dataStream.writeLong(myLong);
            System.out.println("myLong writes " + (dataStream.size() - position) + " bytes.");
            position = dataStream.size();

            dataStream.writeBoolean(myBoolean);
            System.out.println("myBoolean writes " + (dataStream.size() - position) + " bytes.");
            position = dataStream.size();

            dataStream.writeChar(myChar);
            System.out.println("myChar writes " + (dataStream.size() - position) + " bytes.");
            position = dataStream.size();

            dataStream.writeFloat(myFloat);
            System.out.println("myFloat writes " + (dataStream.size() - position) + " bytes.");
            position = dataStream.size();

            dataStream.writeDouble(myDouble);
            System.out.println("myDouble writes " + (dataStream.size() - position) + " bytes.");
            position = dataStream.size();

            dataStream.writeUTF(myString);
            System.out.println("myString writes " + (dataStream.size() - position) + " bytes.");
            position = dataStream.size();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void readPrimitives(Path fileName) {
        try(DataInputStream inputStream = new DataInputStream(Files.newInputStream(fileName))) {
            System.out.println("myInt = " + inputStream.readInt());
            System.out.println("myLong = " + inputStream.readLong());
            System.out.println("myBoolean = " + inputStream.readBoolean());
            System.out.println("myChar = " + inputStream.readChar());
            System.out.println("myFloat = " + inputStream.readFloat());
            System.out.println("myDouble = " + inputStream.readDouble());
            System.out.println("myString = " + inputStream.readUTF());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void writePlayer(Path playerfile, Player player) {
        System.out.println("Writing player to file: " + player);

        try(var outputStream = new ObjectOutputStream(Files.newOutputStream(playerfile))) {
            outputStream.writeObject(player);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void readPlayer(Path playerfile) {
        try(var inputStream = new ObjectInputStream(Files.newInputStream(playerfile))) {
            Player player = (Player)inputStream.readObject();
            System.out.println("Reading player from file: " + player);
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

}

/*
Please read 3_README.txt
 */