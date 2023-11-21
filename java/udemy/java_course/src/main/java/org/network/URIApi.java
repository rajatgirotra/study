package org.network;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.sql.SQLOutput;

/* URLParts.java first
 * WHy do we have two classes URL and URI? What is the difference between them?
 * 1) The URI class is more conforms to the relevant specifications of an internet resource definition. So it is always preferred to use the URI class
 * for resource String manipulation.
 *
 * 2) Unlike URL class, the URI class doesn't provide any functions to download/access the resource. URL class provides openStream(), openConnection(), getContent() API's.
 *    We have toURI() or toURL() api's available to convert from URL to URI and vice-versa.
 *
 * 3) URI objects can represent relative URI's. URL objects contain the absolute definition of the resource.
 *
 * 4) The URI definition is very trivial:
 * schema:schema-specific-part:fragment_identifier.
 *
 * If schema part in a URI object is null, we say it is a relative URI. We have APIs available like resolve() and relativize() to convert between absolute and relative URIs.
 * If the schema-specific-part is hierarchical, we say the URI is NON-OPAQUE. Otherwise, it is opaque. isOpaque() api tells you that.
 * Non-Opaque URI's have many other getter methods like getAuthority(), getHost(), getPort() etc. They are shown below.
 *
 * we have apis available like getSchemeSpecificPart() and getRawSchemeSpecificPart(), the non-raw versions are decoded ones. i.e. the % escape sequences are replaced by the
 * correct character representation.
 */
public class URIApi {
    private static void printURIParts(String uriStr) {
        printURIParts(URI.create(uriStr));
    }
    private static void printURIParts(URI uri) {
        System.out.println("-".repeat(30));
        System.out.println("URI is: " + uri + (uri.isOpaque() ? " It is Opaque" : " It is hierarchical"));
        System.out.println("Absolute or relative: " + (uri.isAbsolute() ? "Absolute" : "Relative"));
        System.out.println("Scheme: " + uri.getScheme());
        System.out.println("Scheme-Specific-Part: " + uri.getSchemeSpecificPart());
        System.out.println("Fragment: " + uri.getFragment());


        if(!uri.isOpaque()) {
            System.out.println("Authority : " + uri.getAuthority());
            System.out.println("UserInfo : " + uri.getUserInfo());
            System.out.println("Host : " + uri.getHost());
            System.out.println("Port : " + uri.getPort());
            System.out.println("Path: " + uri.getPath());
            System.out.println("Query String: " + uri.getQuery());
        }
    }
    public static void main(String[] args) {
        // creating URI objects
        try {
            var voice = new URI("tel:+1-800-9988-9938");
            var web = new URI("http://www.xml.com/#id=_abc");
            var book = new URI("urn:isbn:1-56-92879-9");

            // different ctor than above
            URI styles = new URI("ftp", "anonymous:elharo@ibiblio.org",
                    "ftp.oreilly.com", 21, "/pub/stylesheet", null, null);

            URI styles2 = URI.create(
                    "ftp://énonymous:elharo%20ibiblio.org@ftp.oreilly.com:21/pub/stylesheet");

            // see the difference between toString() and toASCIIString()
            // toASCIIString() will encode non-ASCII characters (like Latin e here)
            System.out.println("Styles2 toString(): " + styles2.toString());
            System.out.println("Styles2 toASCIIString(): " + styles2.toASCIIString());

            printURIParts(voice);
            printURIParts(web);
            printURIParts(book);
            for (String arg : args) {
                printURIParts(arg);
            }
        } catch (URISyntaxException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
URI objects can be used as Keys in HashMap. But how is equality defined? Two URI objects are equal if
1) They both are either opaque or hierarchical.
2) They have the same schema. case is ignored and does not matter.
3) They have the same authority. case is ignored and does not matter.
4) The rest of the URI is case-sensitive.

URI implements comparable and can be ordered.

next URLEncoderDecoder.java
 */
