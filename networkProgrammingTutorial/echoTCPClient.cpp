#include "unp.hpp"

static void str_cli(FILE* stream, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while(Fgets(sendline, MAXLINE, stream) != 0)
    {
        //Write to server
        Writen(sockfd, sendline, strlen(sendline));

        //Now start reading
        if(Readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: Server terminated prematurely");

        Fputs(recvline, stdout);
    }
}

int main(int argc, char* argv[])
{
    //Create a socket
    int sockfd;
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    //Fill the sockaddr_in structure.
    struct sockaddr_in  clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(54321);
    Inet_pton(AF_INET, argv[1], &clientAddr.sin_addr);

    //Now connect to server.
    Connect(sockfd, (SA*)&clientAddr, sizeof(clientAddr));

    //Now get a line from stdin and send to server.
    //Whatever, the server keep sending to stdout
    str_cli(stdin, sockfd);

    return 0;
}
