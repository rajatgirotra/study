package org.network;

import java.io.IOException;
import java.net.InetAddress;

// SimpleInetUsage.java first
public class SpecialAddresses {
    private static int getIPVersion(InetAddress ia) {
        byte[] address = ia.getAddress();
        if(address.length == 4) return 4;
        else if (address.length == 16) return 6;
        else return -1;
    }

    public static void main(String[] args) throws IOException  {
        InetAddress[] ia_arr = InetAddress.getAllByName("www.google.com");
        for(InetAddress ia : ia_arr) {
            System.out.println("Address " + ia.getHostAddress() + " is IPv" + getIPVersion(ia));
        }

        byte[] local = {127, 0, 0, 1};
        InetAddress lo = InetAddress.getByAddress(local);
        System.out.println("Address " + lo.getHostAddress() + " is loopback address? " + lo.isLoopbackAddress());

        // wildcard address. A special address that matches any address on the local system. Your local system
        // may have multiple network interface cards each with its own address. For IPv4, the wildcard address is 0.0.0.0
        // for IPv6, the wildcard address is 0:0:0:0:0:0:0:0
        byte[] wildcard = {0, 0, 0, 0};
        InetAddress wc = InetAddress.getByAddress(wildcard);
        System.out.println("Address " + wc.getHostAddress() + " is wildcard/any address? " + wc.isAnyLocalAddress());

        /* Multicast address. The isMulticastAddress() method returns true if the address is a multicast address,
        false otherwise. Multicasting broadcasts content to all subscribed computers rather than to one particular computer. In IPv4,
         multicast addresses all fall in the range 224.0.0.0 to 239.255.255.255
         */
        byte[] multicast = {(byte)235, 100, 65, 23};
        InetAddress mc = InetAddress.getByAddress(multicast);
        System.out.println("Address " + mc.getHostAddress() + " is multicast address? " + mc.isMulticastAddress());
    }

    // other similar methods are also available. like isMCGlobal(), isSiteLocalAddress() etc etc.
    // NetworkInterfaceTrivial.java next
}
