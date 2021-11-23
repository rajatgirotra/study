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

1) MSS i.e. Maximum Segment Size (i.e the maximum size of TCP payload)
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

connect system call
-------------------
connect() system call starts the 3 way TCP handshake. remember that if a connect() system call fails, you need to close the socket and open again before you call connect again. Also common errors from connect function are:
1) ECONNREFUSED --> this means that the peer TCP has no application listening on the specified port
2) ETIMEDOUT --> this means that SYN request never received a reply. One common reason is that the host IP is non-existant, so there is no TCP peer.
3) EHOSTUNREACH or ENETUNREACH --> this means that the IP address is valid but there is no route to host, so an intermediate router would return "destination unreachable"

bind system call
----------------
bind is used to bind and IP and port to a socket. Normally server processes will bind to a well known port number. and client processes will not get call bind and they will be assigned an ephemeral port by the kernel. common error returned from bind is EADDRESSINUSE. To find the ephemeral protocol address (ip and port) assigned by the kernel, use the getsockname() API.

listen system call
------------------
int listen(int sockfd, int backlog)
listen does two things
1)by default every TCP socket is assumed to be an active socket, ie a client socket that will issue a connect call. so listen converts a socket from active to passive.
2) every tcp server maintains two Q's. one Q of the number of completed connections (which have completed the 3-way handshake) and the second Q of the number of incomplete connections. i.e those for which SYN is received from client.

backlog is the total of both these Q's. this means if backlog is 1 and you already have one connection. the second connection from another client will be rejected. As connections are completed, they are only removed from the completed connections Q, when the server calls accept.

accept system call
------------------
sockaddr_in cliaddr;
int clilen = sizeof(cliaddr);
int connfd_or_error = accept(listen_fd, reinterpret_cast<sockaddr*>(&cliaddr), &clilen);
accept() returns the connected socket descriptor if successful, otherwise will return an error. also the cliaddr, and clilen are value-result arguments (ie, both input and output parameters). cliaddr is filled with the protocol address (IP and port) of the TCP client peer

concurrent servers
-----------------
for writing concurrent servers, the main server can fork a new process to handle the new client connection using the fork() and exec() system calls.
pid_t fork(void); 
fork() is really easy. it is called once but returns twice. It returns 0 in the child process. and it returns the pid of the child process in the parent process. it returns 0 because every process has exactly one parent and the process can all getppid() to get its parent pid. however for a parent to know of all its children, it must do its own book-keeping when the child pid id returned from the fork() call. after a call to fork both parent and child share the open descriptors. usually in concurrent systems, the parent process will close the client socket and the client will close the listening socket.

also remember the 6 overloaded exec() family of calls used to create a new process. easy way to remember is execl. execl takes a list of arguments to the process as multiple char* arguments.

execl(const char* pathname, const char* arg0, const char* arg1, const char* arg2,... const char* argn) --> the last const char* must be nullptr.

execle (e means function also takes a const char* envp[])
execle(const char* pathname, const char* arg0, const char* arg1, const char* arg2,... const char* argn, const char* envp[]) --> the last const char* must be nullptr.

execlp (p means the function takes a filename and not a pathname). filename must be found in $PATH.
execlp(const char* filename, const char* arg0, const char* arg1, const char* arg2,... const char* argn) --> the last const char* must be nullptr.

then you have execv. --> execv takes list of arguments as an array.
execv(const char* pathname, const char* argv[]);
execve(const char* pathname, const char* argv[], const char* envp[]);
execvp(const char* filename, const char* argv[]);

Also REMEMBER that calling close(sockfd) should start the TCP connection termination sequence. ie a FIN should be sent. however these descriptors are reference counted. so only when the reference count reaches 0, then the termination sequence will start.

getsockname()/getpeername()
---------------------------
both have same declartion

sockaddr_in serveraddr;
int len = sizeof(serveraddr);
getsockname(int sockfd, reinterpret_cast<sockaddr*>(&serveraddr), &len);
getpeername(int sockfd, reinterpret_cast<sockaddr*>(&serveraddr), &len);

use of getsockname/getpeername
1) client TCP
   a) can use getsockname() to get the local protocol address (family, ip, port) assigned by the kernel. usually client tcp doesnt call bind so kernel assign ip and port.
   b) can use getpeername() on the connected socket to get the protocol address (ip, port) of the TCP server.
2) server TCP
   a) if server calls bind with port 0 (ie kernel supposed to assign a port), getsockname() will return the local protocol address
   b) if server calls bind with INADDR_ANY, then after accept(), getsockname() can return the local protocol address
   c) if the server forks() and execs(), we can pass the connected socket descriptor to the new program via the command line, and the new program can call getpeername() to get the protocol        address of the client which it should handle.


