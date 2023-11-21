package org.network;

import java.net.MalformedURLException;
import java.net.URL;

/*
URL is just a kind of URI. A URL has a structure like:
protocol://server/path?queryString.

Similarly, a URI is used to identify any resource on the internet. like a file, a mail in someone's inbox, a filtered set of results on some website etc.
like URL, URI's also has a structure. It has a

schema: schema-specific part (the schema-specific part various for every scheme, but normally has a hierarchical form like: //authority/path?query

schema could be:
file
data
ftp
http
mailto
telnet
urn (uniform resource name)
Java also has some non-standard schemes like rmi, jndi, jar, doc for example

So what is protocol in URL is scheme in URI
what is server in URL is authority in URI.

Each JVM supports a list of URL Protocols. Let's write a program to see what protocols are supported. JVM throws MalformedURLException if the URL is invalid.
 */
public class URLS {
    private static void testProtocol(String urlStr) {
        try {
            var url = new URL(urlStr);
        } catch (MalformedURLException e) {
            String protocol = urlStr.substring(0, urlStr.indexOf(':'));
            System.out.printf("%s is not supported%n", protocol);
        }
    }
    public static void main(String[] args) {
        // http & https
        testProtocol("https://www.google.com/");
        testProtocol("http://www.google.com/");

        //ftp
        testProtocol("ftp://ibiblio.org/pub/languages/java/javafaq/");

        //smtp
        testProtocol("mailto:rajatgirotra@yahoo.com");

        //telnet
        testProtocol("telnet://abcd.xyz.pqr/");

        // local filesystem
        testProtocol("file:///etc/passwd");

        //ldap
        testProtocol("ldap://ldap.server.com/o=University%20of%20Michigan,c=US?postalAddress");

        //jar
        testProtocol("jar:http://cafeaulait.org/books/javaio/ioexamples/javaio.jar!");

        //NFS
        testProtocol("nfs://changkat.primary.edu/");

        // custom protocols
        testProtocol("jdbc:mysql://server.com/NEWS"); // jdbc
        testProtocol("rmi://ibiblio.org/RenderEngine"); // rmi (Remote method invocation)

        testProtocol("doc:/UsersGuide/release.html");
        testProtocol("netdoc:/UsersGuide/release.html");
        testProtocol("systemresource://www.adc.org/+/index.html");
        testProtocol("verbatim:http://www.adc.org/");
    }
}

/*
 JDBC and RMI are actually supported by the java.rmi and java.sql packages respectively.
 DumpURLData.java next
 */