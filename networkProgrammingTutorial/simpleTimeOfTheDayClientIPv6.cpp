/* Please read simpleTimeOfDayClient.cpp first.
 * Our previous code was protocol dependent on IPv4 as we created a sockaddr_in address structure which is specific to IPv4.
 * Let's modify our source now, so that it works with IPv6 version.
 */

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int argc, char* argv[]) 
{
    int sockfd, n;
    char ch[256] = { 0 };
    struct sockaddr_in6 serverAddr; //Change 1.


    /* The first thing you need to do is to create a socket, which is a combination of IP and Port No.
     * Here we create a Internet (AF_INET) stream socket (SOCK_STREAM), which is a fancy name for
     * a TCP socket. This basically returns a file descriptor which is later used in other system calls like connect().
     * sockfd = socket(int socket_family, int socket_type, int protocol); 
     * On success, 0 is returned. On failure, -1 is returned and errno is set accordingly.
     */
    sockfd = socket(AF_INET6, SOCK_STREAM, 0); //Change 2.

    /* Next, we fill in an Internet socket address structure (a sockaddr_in structure named servAddr) with the server's IP
     * address and port number. We set the entire structure to 0 using memset, set the address family to AF_INET, set the
     * port number to 13 (which is the well-known port of the daytime server on any TCP/IP host that supports this service),
     * and set the IP address to the value specified as the first command-line argument (argv[1]).
     * The port and IP must in a specific format. So:
     * 1] For port we use htons (ie. host to network short), and
     * 2] For IP, we use inet_pton (ie. presentation to numeric) to convert the ASCII command line argument into the
     *    proper format.
     */
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin6_family = AF_INET6; //Change 3.
    serverAddr.sin6_port = htons(13); //Change 4.
    n = inet_pton(AF_INET6, argv[1], &serverAddr.sin6_addr); //Change 5.

    /* int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
     * The connect() function is used to establish a TCP connection with the server specified in the socket server
     * address structure specified as the second argument. 
     * One interesting thing to note here: the second argument is "struct sockaddr" which is a generic socket address
     * structure. "sockaddr_in" or "sockaddr_in6" are IPv4 and IPv6 specific structures. But you can always safely upcast
     * them to "sockaddr".
     */
    n = connect (sockfd, (const sockaddr*)&serverAddr, sizeof(serverAddr));

    /* We must be careful when using TCP because it is a byte-stream protocol with no record boundaries. The daytime
     * server's reply is normally a 26-byte string of the form "Mon May 26 20 : 58 : 40 2003\r\n"
     * With a byte-stream protocol, these 26 bytes can be returned in numerous ways: a single TCP segment containing all
     * 26 bytes of data, in 26 TCP segments each containing 1 byte of data, or any other combination that totals to 26 bytes.i
     * Normally, a single segment containing all 26 bytes of data is returned, but with larger data sizes, we cannot 
     * assume that the server's reply will be returned by a single read. Therefore, when reading from a TCP socket, 
     * we always need to code the read in a loop and terminate the loop when either read returns 0 (i.e., the other end 
     * closed the connection) or a value less than 0 (an error).
     * In this example, the end of the record is being denoted by the server closing the connection. This technique is 
     * also used by version 1.0 of the Hypertext Transfer Protocol (HTTP). Other techniques are available. For example, 
     * the Simple Mail Transfer Protocol (SMTP) marks the end of a record with the two-byte sequence of an ASCII carriage 
     * return followed by an ASCII linefeed. Sun Remote Procedure Call (RPC) and the Domain Name System (DNS) place a 
     * binary count containing the record length in front of each record that is sent when using TCP. The important 
     * concept here is that TCP itself provides no record markers: If an application wants to delineate the ends of 
     * records, it must do so itself and there are a few common ways to accomplish this.
     */
    while( (n = read(sockfd, ch, 255)) > 0) {
        ch[255] = 0;
        cout << ch;
        //fputs(ch, stdout);
    }
    return 0;
}
