package org.network;

import java.io.IOException;
import java.net.URL;

// URLToText.java first
/*
URL.getContent() has two variants. The first one tries to find out the type of content returned from the Content-Type in the HTTP header.
and will then return a java.lang.Object. Example:
1) If response type is HTML, return Object might be an instance of InputStream
2) If response type is Audio, return Object might be an instance of sun.applet.AppletAudioClip
3) If response type is an image, return Object might be an instance of sun.awt.image.URLImageSource
 */
public class URLReadContent {
    public static void main(String[] args) {
        assert args.length > 0;
        try {
            String urlStr = args[0];
            var url = new URL(urlStr);
            var obj = url.getContent();
            System.out.println("URL.getContent() returned java.lang.Object of type: " + obj.getClass().getName());
        } catch(IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/* The other overloaded version is also trivial. You can read it online
* Next URLParts.java
*/
