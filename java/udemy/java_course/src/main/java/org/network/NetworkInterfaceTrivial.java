package org.network;

import java.lang.reflect.Array;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Arrays;
import java.util.Enumeration;

/* NetworkInterface is a trivial class representing a physical or virtual NetworkInterface on the local system.
* Multiple virtual interfaces can be bound to the same physical hardware */
public class NetworkInterfaceTrivial {
    public static void main(String[] args) {
        // list all available network interfaces
        try {
            Enumeration<NetworkInterface> nis = NetworkInterface.getNetworkInterfaces();
            while(nis.hasMoreElements()) {
                var ni = nis.nextElement();
                System.out.println("Network Interface: " + ni);
            }

            // get NetworkInterface by name. on unix names are like eth0, eth1 etc.
            NetworkInterface ni_byName = NetworkInterface.getByName("wireless_0");
            if(ni_byName == null) {
                System.out.println("Could not find network interface wireless_0");
            } else {
                System.out.println("-".repeat(30));
                System.out.printf("Details of wireless_0 interface%n" +
                        "Display Name: %s%n" + "MTU: %s%n", ni_byName.getDisplayName(), ni_byName.getMTU());
                var bytes = ni_byName.getHardwareAddress();
                int[] hw_addr = new int[6];
                for(int i = 0; i < bytes.length; ++i) {
                    hw_addr[i] = bytes[i] < 0 ? (int)(bytes[i]+256) : bytes[i];
                }
                System.out.println("Hardware address: " + Arrays.toString(hw_addr));
                System.out.println("InterfaceAddress (IP/SubnetMask/BroadcastAddress)");
                var if_addresses = ni_byName.getInterfaceAddresses(); //  In short, it's an IP address, a subnet mask and a broadcast address for this Network Interface
                for(var if_addr : if_addresses) {
                    System.out.println(if_addr);
                }
                System.out.println("InetAddresses");
                Enumeration<InetAddress> addresses = ni_byName.getInetAddresses();
                while (addresses.hasMoreElements()) {
                    System.out.println(addresses.nextElement());
                }
                System.out.println("-".repeat(30));
            }

            // get NetworkInterface by address.
            InetAddress ia = InetAddress.getByName("127.0.0.1");
            NetworkInterface ni_lo = NetworkInterface.getByInetAddress(ia);
            if(ni_lo == null) {
                System.out.println("Weird. No local loopback address.");
            }
            System.out.println("Loopback interface: " + ni_lo);

        } catch (SocketException | UnknownHostException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
URLS.java next
 */