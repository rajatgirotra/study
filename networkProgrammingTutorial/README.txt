you already know the basics of writing a TCP client and server.

TCP client
----------
socket()
fill the sockaddr_in socket address structure with protocol family (AF_INET), host and port
connect()
read()


TCP server
---------
socket()
fill the sockaddr_in socket address structure with protocol family (AF_INET), host and port
bind()
listen()
accept()
// you get a connected socket
write() to the connected socket.


TCP connection is a 3-way handshake.
1) client sends a SYN request, example: SYN J
2) server acknowldeges SYN J and sends his own SYN together in the same segment. example: ACK J+1, SYN K
3) client acknowldeges servers SYN by sending ACK K+1

basically in the acknowldegments, the TCP peer is sending back the next sequence number (J+1, K+1) they are expecting.

also in the handshake, no data is sent. but few options are advertised.

1) MSS i.e. Maximum Segment Size
2) Maximum window size.

To understand these lets understand a few other things first.

1) IPv4 packet has a 20 byte header, 40 byte options followed by data.
2) TCP segment also has a 20 byte header, 40 byte options followed by data.

IPv4 encapsulates a TCP segment.
Also many networks have an MTU (maximum transmission unit) dictated by the hardware. For example, ethernet has a maximum MTU of 1500 bytes. this means that if you send an IP packet > 1500 bytes in total size, it will need to be fragmented and then sent over the ethernet. the fragmentation can be done by the host sending the packet or by the router forwarding the packet.

However IPv4 header has a Dont Fragment (DF) flag. If set to 1, the packet can't be fragmented. in such a case if the ipv4 packet size is greater than the path MTU, the packet cannot be sent and is rejected with error by the router. "ICMP destination unreachable, fragmentation needed but DF bit set".

TCP implementations can also do path MTU discovery. they can send datagrams of large size with DF bit set. If they get back the error above, they can reduce the size of the datagram and retransmit.

now the IPv4 protocol standard says that the minimum reassembly buffer size. ie the minimum size of the payload (data) that an IPv4 packet can carry and which the TCP implementations must support is 576 bytes. So now in the initial TCP handshake, if peers dont advertize the MSS size, the default MSS is 576 bytes. However TCP implementations can support much more then 576 bytes of payload. they are restricted mostly by the path MTU. because if they advertise that they can handle more than path MTU, this means all IPv4 packets will carry much more data than path MTU and will cause a lot of fragmentation. So mostly the MSS value advertised by TCP peers over ethernet is 1460. (1500-20 bytes of header for ipv4 and 20 bytes of header for TCP segment).

Also you know about the TCP/UDP features

UDP
---
connection less
non-reliable
packet loss can occur
no acknowldegments
duplicated can arrive
out of sequence delivery
no flow control
can be full duplex
UDP implementations dont have a data send buffer in the kernel like TCP implementations do. So when the write() call returns it means the data is written out to the datalink queue.

TCP
---
connection oriented
reliable
best effort delivery
flow control
no out of sequence packets
no duplicats
full duplex
TCP implementations have a send buffer in the kernel. so when the write() call returns that the data is written to kernel buffer and application buffer can be re-used.
TCP also continuously keeps doing RTT calculation ie calculates the Round Trip Time. this helps TCP to understand when an acknowldegment should have arrived and whether it should re-transmit.
TCP also continuously advertises its window size. ie the amount of empty buffer space the TCP has to accept more data from its peer. that's how flow control is implemented.

Socket Pair
----------
socket is a IP,Port pair. Socket Pair is IP,Port pair of both the client and server.

TIMED_WAIT
---------
the TCP peer initiating the close of connection (i.e which sends the inital FIN) has to go through the TIMED_WAIT state for a period of 2MSL (2 times Maximum Segment Lifetime). MSL is defined differently by different TCP implementations but is normally between 30 seconds to 2 mins. So 2 MSL is roughly 1 minute to 4 minutes. Why we have this?

1) If the last FIN (sent by the peer doing the passive close) is lost, the peer doing the active close will need to re-transmit the ACK for it. So it must remain in TIMED_WAIT state for some time

2) If another connection with the same socket pair is created, there are chances that an old packet from the last connection can make its way in the new connection. So 2 MSL time just gives the packet sufficient time to die in the network so that the new connection doesnt get any packets from an old connection

