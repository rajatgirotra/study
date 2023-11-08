package org.input_output;

import org.jetbrains.annotations.NotNull;

import java.io.*;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;

public class TransferToUsage {
    public static void main(String[] args) {
        URI uri = URI.create("https://api.census.gov/data/2019/pep/charagegroups?get=NAME,POP&for=state:*");
        try (var urlInputStream = uri.toURL().openStream()) {
            urlInputStream.transferTo(System.out);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // same as above but dump to file
        Path outFile = Path.of("out.txt");
        try(var urlInputStream = new InputStreamReader(uri.toURL().openStream());
            var writer = Files.newBufferedWriter(outFile)) {
            urlInputStream.transferTo(writer);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        // same as above but transform before you write
        Path outCSV = Path.of("out.csv");
        try(var urlInputStream = new InputStreamReader(uri.toURL().openStream());
            var printWriter = new PrintWriter(outCSV.toFile())) {
            var writer = new Writer() {
                @Override
                public void write(@NotNull char[] cbuf, int off, int len) throws IOException {
                    String content = new String(cbuf, off, len).trim();
                    content = content.replaceAll("\\[", "").trim();
                    content = content.replaceAll("\\]", "");
                    printWriter.write(content);
                }

                @Override
                public void flush() throws IOException {
                    printWriter.flush();
                }

                @Override
                public void close() throws IOException {
                    printWriter.close();
                }
            };
            urlInputStream.transferTo(writer);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}

/*
read DirectoryFileChallenge.java next
 */