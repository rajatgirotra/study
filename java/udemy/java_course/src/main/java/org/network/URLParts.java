package org.network;

/*
URLReadContent.java first
The whole URL format has:
http://www.ibiblio.org/javafaq/books/jnp/index.html?isbn=1565922069#toc
1) protocol or scheme (http above)
2) host or authority (www.ibiblio.org)
3) path (javafaq/books/jnp/index.html)
4) query string (isbn=1565922069)
5) fragment identifer or ref or section (toc)

The host can be further broken down into userInfo, host and port (eg: in http://admin@www.blackstar.com:8080/), userInfo is admin,
www.blackstar.com is host and 8080 is port.

Now we have many functions on URL class which return these parts of the URL. Let's explore it.
 */

import java.io.IOException;
import java.net.URL;

public class URLParts {
    public static void main(String[] args) {
        // for each URL in argument, split it into parts and print it.
        for(int i = 0; i < args.length; ++i) {
            System.out.println("-".repeat(30));
            try {
                URL url = new URL(args[i]);
                System.out.println("URL: " + url);
                System.out.println("protocol: " + url.getProtocol());
                System.out.println("authority: " + url.getAuthority());
                System.out.println("user_info: " + url.getUserInfo());
                System.out.println("host: " + url.getHost());
                System.out.println("port: " + url.getPort());
                System.out.println("file: " + url.getFile());
                System.out.println("path: " + url.getPath()); // getFile and getPath() are almost same. getPath() does not include query string
                System.out.println("query string: " + url.getQuery());
                System.out.println("fragment identifier: " + url.getRef());
            } catch(IOException e) {
                e.printStackTrace();
            }
            finally {
                ;
//                System.out.println("-".repeat(30));
            }

        }
    }
}

/*
Please note that two URL objects are equal if they have the same values for host, port, path, query string and fragment identifier.
However, we SHOULD NEVER USE URL as key in HashMap because the equals() method tries to resolve the host using DNS which is a blocking I/O operation.
It needs to do it so that it can make sure that http://ibiblio.org and http://www.ibiblio.org are the same hosts.

Also prefer to use URI as key in HashMap as it does not do DNS lookup.

If you want to compare two URL ignoring the fragment identifier, you can use "public boolean sameFile(URL other)" API of the URL class.

Also note that URL::toString() and URL::toExternalForm() are the same. No difference

next URIApi.java
 */