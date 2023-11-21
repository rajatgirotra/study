package org.network;

import java.net.URLDecoder;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;

// URLApi.java first
/*
URI specification allows the following characters in the URI string
1) English alphabets A-Z, a-z
2) Digits 0-9
3) punctuation characters -, _, ., !, ~, *, ', (, )
4) Other characters like /, &, =, +, @, ?, #, ;, $, % are characters which are present for specific purposes for building up the URI.
5) Non english alphabets are also allowed.

However, these non english characters and the other characters (point 4 above, if used as part of the name, and not as a separator between parts of the URI) must be encoded.
Java provides URLEncoder.encode() function and URLDecoder.decode() functions to handle this. The URLEncoder.encode() is very aggressive and will encode all characters, whether
they are used as part of the URL or used in a name.
 */
public class URLEncoderDecoder {
    private static void encode(String str) {
        System.out.println("uri: " + str + ", encoded: " + URLEncoder.encode(str, StandardCharsets.UTF_8));
    }

    public static void main(String[] args) {
        encode("This string has spaces"); // note that in URI spec, spaces are encoded as + sign.
        encode("This*string*has*asterisks");
        encode("This%string%has%percent%signs");
        encode("This+string+has+pluses");
        encode("This/string/has/slashes");
        encode("This\"string\"has\"quote\"marks");
        encode("This:string:has:colons");
        encode("This~string~has~tildes");
        encode("This.string.has.periods");
        encode("This&string&has&ampersands");
        encode("Thiséstringéhasé non-ASCII characters");

        // decoding is trivial
        String input = "https://www.google.com/search?hl=en&as_q=Java&as_epq=I%2FO";
        String output = URLDecoder.decode(input, StandardCharsets.UTF_8);
        System.out.println(output);
    }
}

/* Next 2_README.txt */