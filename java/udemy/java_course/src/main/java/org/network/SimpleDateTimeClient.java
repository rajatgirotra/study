package org.network;

// 3_README.txt first

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

// simple TCP day time client
public class SimpleDateTimeClient {
    public static void main(String[] args) {
        assert (args.length == 2); // args[0] is server and args[1] is port
        int port = Integer.parseInt(args[1]);

        // create a client socket
        try (Socket socket = new Socket(args[0], port)) {
            // set socket timeout SO_TIMEOUT option, so that blocking read calls on the socket don't remain blocked forever
            socket.setSoTimeout(15000); // 15000 milliseconds
            // to append response in text from server
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            int c;
            StringBuilder time = new StringBuilder();
            while ((c = reader.read()) != -1) {
                time.append((char) c);
            }
            System.out.printf("Time is %s", time.replace(0, 1, "")); // first character is <NEWLINE> so just removing it.
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
Here we know that the NTP protocol at port 13 returns text/character data.
Let's write a program to get the time as a 4 byte unsigned integer in big endian format from the same host at port 37 instead.

SimpleTimeProtocol.java next
 */