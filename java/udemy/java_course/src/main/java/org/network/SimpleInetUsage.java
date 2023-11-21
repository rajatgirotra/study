package org.network;

import java.io.IOException;
import java.net.InetAddress;
import java.util.Arrays;

// 1_README.txt first
public class SimpleInetUsage {
    public static void main(String[] args) throws IOException  {
        // get InetAddress using hostname.
        InetAddress add1 = InetAddress.getByName("www.oracle.com"); // will perform a DNS lookup.
        System.out.println("add1: " + add1 + " hostname: " + add1.getHostName());

        InetAddress[] allGoogleIPs = InetAddress.getAllByName("www.google.com"); // will return both IPv4 and IPv6 addresses
        for(InetAddress add : allGoogleIPs) {
            System.out.println(add);
        }

        // getLocalHost
        InetAddress add2 = InetAddress.getLocalHost();
        System.out.println("Localhost: " + add2);
        // can also use the NetworkInterface class to create InetAddress for local IP addresses.

        // manually create an InetAddress using a hostname and IPAddress without using a DNS lookup.
        byte[] address = {74, 125, (byte)200, 99};
        InetAddress add3 = InetAddress.getByAddress(address);
        String hostname = add3.getHostName(); // A DNS lookup happens whenever a InetAddress is created from an IP Address.
        System.out.println("add3: " + add3 + " hostname: " + hostname);

        InetAddress add4 = InetAddress.getByAddress("www.abcd.com", address);
        String hn = add4.getHostName(); // No DNS lookup happens as we explicitly associate a hostname with an IPAddress
        System.out.println("add4: " + add4 + " hostname: " + hn + " getHostAddress: " + add4.getHostAddress() + " getAddress: " + Arrays.toString(add4.getAddress()));
        // getHostAddress() and getAddress() are very trivial. Note why some entry can be negative as java doesn't have unsigned byte.
        // so anything greater than 127 needs to be cast to integer (signedByte < 0 ? signedByte + 256 : signedByte)

        InetAddress add5 = InetAddress.getByAddress("www.abcd.com", address);
        String hname = add5.getCanonicalHostName(); // getCanonicalHostName() is more aggressive compared to getHostName(). It will always do a DNS lookup
        // if the DNS Server is available and may replace the existing hostname in the cache.
        System.out.println("add5: " + add5 + " hostname: " + hname);

        /* two InetAddress are equal if their IP addresses are equal. hostname may or may not be same. hashcode() also takes IPAddress only into account */
        InetAddress ia_left = InetAddress.getByAddress("www.abc.com", address);
        InetAddress ia_right = InetAddress.getByAddress("www.xyz.com", address);
        System.out.println("ia_left: " + ia_left + " hashcode: " + ia_left.hashCode());
        System.out.println("ia_right: " + ia_right + " hashcode: " + ia_right.hashCode());
        System.out.println("ia_left.equals(ia_right): " + ia_left.equals(ia_right));
    }
}

/* SpecialAddresses.java next */
