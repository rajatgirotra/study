#include "unp.hpp"

int main(int argc, char* argv[])
{
    int sockfd;

    if(argc != 2)
        err_quit("Usage: a.out <IPAddress>");

    //Create a TCP/IPv4 socket.
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    //Create a sockaddr_in structure and enter the details of the server to connect to
    struct sockaddr_in serverAddr;
    //Wipe it to 0 first
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12585);
    Inet_pton(AF_INET, argv[1], &serverAddr.sin_addr);

    //Connect to Server now
    Connect(sockfd, (SA*)&serverAddr, sizeof(serverAddr));

    //Now start reading
    int n;
    char buff[MAXLINE + 1];
    while ( (n = Read(sockfd, buff, MAXLINE)) > 0)
    {
        buff[MAXLINE] = 0;
        Fputs(buff, stdout);         
    }
    return 0;
}
