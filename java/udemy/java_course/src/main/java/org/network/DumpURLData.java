package org.network;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;

// URLS.java first
public class DumpURLData {
    public static void main(String[] args) {
        try {
            URL u = new URL("https://www.google.com");
            try (var in = u.openStream()) { // URL.openStream() provides an InputStream
                int c;
                while ((c = in.read()) != -1) {
                    System.out.write(c);
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
Next lets try to read data from a URL passed as argument as text instead of raw bytes.
URLTOText.java next
 */