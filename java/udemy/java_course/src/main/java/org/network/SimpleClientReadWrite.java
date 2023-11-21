package org.network;

import java.io.*;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

/*
Simple TCP client which connects to a dictionary server at dict.org port 2628.
and sends a command "DEFINE fd-eng-lat gold" to get the name of the gold in latin.
 */
public class SimpleClientReadWrite {
    private static final String HOST = "dict.org";
    private static final int PORT = 2628;

    public static void main(String[] args) {
        assert (args.length > 1);
        try (var socket = new Socket(HOST, PORT);
             var writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8));
             var reader = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8))) {
            for (String word : args) {
                writeAndReadSocket(writer, reader, word);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static void writeAndReadSocket(BufferedWriter writer, BufferedReader reader, String word) {
        try {
            writer.write("DEFINE fd-eng-lat " + word + "\r\n");
            writer.flush(); // flush the buffer

            // read now
            for (String line = reader.readLine(); line != null; line = reader.readLine()) {
                if (line.startsWith("250 ")) {
                    // all is good. definition is returned. can exit now
                    return;
                } else if (line.startsWith("552 ")) {
                    // no definition found.
                    System.out.println("No definition found for word [" + word + "]");
                    return;
                } else if (line.matches("\\d\\d\\d .*")) {
                    //ignore all other codes
                    continue;
                } else if (line.trim().equals(".")) continue;
                System.out.println(line);
            }

            writer.write("quit\r\n");
            writer.flush();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
The "Socket sock = new Socket(HOST, PORT)" actually initiates TCP three stage handshake.

Also, if you want only half duplex communication, you can close the input or output connection using:
1) shutdownInput() method -> Any attempts to read after this call will return -1.
2) shutdownOutput() method -> Any attempts to write after this call will throw IOException.
socket.close() still needs to be called the end when connection is terminated.

There are other constructors of the Socket class which take the local network interface and local port also which should be used to make a connection.
and there are constructors which do not do anything (i.e. do not initiate a 3 stage handshake). They need to call Socket::connect() function explicitly to
initiate a connection. This ctor is also useful when you want to set some socket options which can only be set prior to initiating a connection.

Connecting via a proxy server
-----------------------------
SocketAddress proxyAddress = new InetSocketAddress(PROXY_SERVER, PROXY_PORT);
Proxy proxy = new Proxy(Proxy.Type.SOCKS, proxyAddress);
Socket socket = new Socket(proxy);
SocketAddress destination = new InetSocketAddress(REMOTE_HOST, REMOTE_PORT);
socket.connect(destination);

MISLEADING isClosed() and isConnected() methods
-----------------------------------------------
isClosed() -> true, if socket is closed, false otherwise. But what if socket was never opened? isClosed() returns false in those cases which is misleading.

isConnected() -> true, if the socket was ever connected in the past to the remote host. Doesn't matter what its status is now.

To check if socket is open the correct check should be:

boolean connected = socket.isConnected() && ! socket.isClosed();

4_README.txt next
 */