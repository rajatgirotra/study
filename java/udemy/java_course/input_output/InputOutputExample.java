package input_output;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class InputOutputExample {
    public static void main(String[] args) {
        // very easy to implement reader and writer.

        try  {
            BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"));
            writer.write("This is first line\n");
            writer.write("This is second line\n");
            writer.close();

            BufferedReader reader = new BufferedReader(new FileReader("output.txt"));
            String line;
            while((line = reader.readLine()) != null) {
                System.out.println("Read line: " + line);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}