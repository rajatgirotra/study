#include "unp.hpp"

static void str_echo(int connfd)
{
    //Read whatever the client sends, prefix "From Server: ", and send it back again.
    ssize_t n;
    char buf[MAXLINE];
    char tempBuf[MAXLINE];

    again:
        while( (n = read(connfd, buf, MAXLINE)) > 0 )
        {
            memset(tempBuf, 0, MAXLINE);
            strncpy(tempBuf, buf, strlen(buf) + 1);
            strcpy(buf, "From Server: ");
            strncat(buf, tempBuf, sizeof(tempBuf));
            Writen(connfd, buf, strlen(buf));
            memset(buf, 0, MAXLINE);
        }

        if( n < 0 && errno == EINTR)
            goto again;
        else if(n < 0)
            err_sys("str_echo: read error");
}

int main()
{
    int listenfd;
    //Create a Socket descriptor first
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    //Create a sockaddr_in structure and bind a server port and IP.
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54321);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(listenfd, (SA*)&serverAddr, sizeof(serverAddr));

    //Set the listen q size
    Listen(listenfd, LISTENQ);

    //For each client connection, create a new process and handle the client request
    //on that thread.
    struct sockaddr_in clientAddr;
    socklen_t cliLen;
    for(; ;)
    {
        int connfd = Accept(listenfd, (SA*)&clientAddr, &cliLen);
        
        pid_t child;
        child = Fork();
        if(child == 0)
        {
            //In Child process
            Close(listenfd);
            str_echo(connfd);
            exit (0);
        }

        Close(connfd);
    }
}


