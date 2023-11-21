package org.network;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Arrays;

/*
DumpURLData.java first
 */
public class URLToText {
    public static void main(String[] args) {
        assert args.length > 0;
        String urlStr = args[0];
        try {
            var url = new URL(urlStr);
            try(var reader = new BufferedReader(new InputStreamReader(url.openStream()))) {
                int c;
                while((c = reader.read()) != -1) {
                    System.out.print((char)c);
                }
            }
        } catch(IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/* The result may look fine, but we have committed a cardinal sin. We have assumed that the resource is all text.
Which we should never assume that a URL resource is all text. It could be a GIF, JPEG, MP3 or something else entirely.
in fact, even if it is text, how do you know what is the URL file encoding? Here we are just using the default decoder provided by the InputStreamReader class.

Normally URL resources provide the encoding information either as part of HTTP response headers or also in the data itself using HTML META Tags or
by providing <?xml version="1.0" encoding="UTF-8"?> in an XML resource.

So never assume that a URL resource is always text and don't assume the file encoding also.
Rely on URL.openConnection() API to provide you a URLConnection object. This object can be used to read all the metadata for the request.

URLConnection uc = u.openConnection();
InputStream in = uc.getInputStream();
// read from InputStream as usual.

URLReadContent.java next
 */
