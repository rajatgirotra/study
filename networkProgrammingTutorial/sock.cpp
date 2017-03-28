#include "unp.hpp"

int Socket(int family, int port, int protocol)
{
    int sockfd = -1;
    sockfd = socket(family, port, protocol);
    if(sockfd < 0)
        err_sys("socket Error");
    return sockfd;
}

void Connect(int sockfd, const struct sockaddr* sa, socklen_t len)
{
    if(connect(sockfd, sa, len) < 0)
        err_sys("connect Error");
}

void Bind(int sockfd, const struct sockaddr* sa, socklen_t len)
{
    if(bind(sockfd, sa, len) < 0)
        err_sys("bind error");
}

void Listen(int sockfd, int backlog)
{
    if(listen(sockfd, backlog) < 0)
        err_sys("listen error");
}

void Inet_pton(int family, const char* strptr, void* addrptr)
{
    int n;
    n = inet_pton(family, strptr, addrptr);
    if(n < 0)
        err_sys("inet_pton error for %s", strptr);
    else if(n == 0)
        err_quit("inet_pton error for %s", strptr);
}

const char* Inet_ntop(int family, const void* addrptr, char* strptr, size_t len)
{
    const char* ptr;
    if(strptr == 0)
        err_quit("NULL 3rd argument to Inet_ntop");

    ptr = inet_ntop(family, addrptr, strptr, len);

    if(ptr == 0)
        err_sys("inet_ntop error");

    return ptr;
}

void Close(int sockfd)
{
    if(close(sockfd) == -1)
        err_sys("close error");
}

int Accept(int sockfd, struct sockaddr* sa, socklen_t* len)
{
    int connfd = -1;
    connfd = accept(sockfd, sa, len);
    if(connfd == -1)
        err_sys("accept error");
    return connfd;
}

void Write(int sockfd, void* ptr, size_t nBytes)
{
    if(write(sockfd, ptr, nBytes) < 0)
        err_sys("write error");
}

int Read(int sockfd, void* ptr, size_t nBytes)
{
    int n;
    n = read(sockfd, ptr, nBytes);
    if(n == -1)
        err_sys("read error");
    return n;
}

int readn(int fd, void* ptr, size_t n)
{
    int nRead, nLeft;
    nLeft = n;
    char* chPtr;

    chPtr = (char*)ptr;
    while (nLeft > 0)
    {
        nRead = read(fd, chPtr, nLeft);
        if(nLeft < 0)
        {
            if(errno == EINTR)
            {
                nRead = 0;
                continue;
            }
            else
                return -1;
        }
        else if(nRead == 0)
            break;

        nLeft -= nRead;
        chPtr += nRead;
    }
    return (n - nLeft);
}

int Readn(int fd, void* ptr, size_t n)
{
    int nRead = readn(fd, ptr, n);
    if(nRead < 0)
        err_sys("readn error");

    return nRead;
}

int writen(int fd, const void* ptr, size_t n)
{
    int nLeft, nWritten;
    nLeft = n;
    char* chPtr = (char*)ptr;

    while(nLeft > 0)
    {
        nWritten = write(fd, chPtr, nLeft);
        if(nWritten <= 0)
        {
            if(nWritten < 0 && errno == EINTR)
            {
                nWritten = 0;
                continue;
            }
            else
                return -1;
        }

        nLeft -=nWritten;
        chPtr += nWritten;
    }
    return (n);
}

void Writen(int fd, const void* ptr, size_t nBytes)
{
    if(writen(fd, ptr, nBytes) <= 0)
        err_sys("writen error");
}


static int  read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];

static ssize_t
my_read(int fd, char *ptr)
{

    if (read_cnt <= 0) {
again:
        if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return(-1);
        } else if (read_cnt == 0)
            return(0);
        read_ptr = read_buf;
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return(1);
}

    ssize_t
readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c, *ptr;

    ptr = (char*)vptr;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;  /* newline is stored, like fgets() */
        } else if (rc == 0) {
            *ptr = 0;
            return(n - 1);  /* EOF, n - 1 bytes were read */
        } else
            return(-1);     /* error, errno set by read() */
    }

    *ptr = 0;   /* null terminate like fgets() */
    return(n);
}

static    ssize_t
readlinebuf(void **vptrptr)
{
    if (read_cnt)
        *vptrptr = read_ptr;
    return(read_cnt);
}
/* end readline */

    ssize_t
Readline(int fd, void *ptr, size_t maxlen)
{
    ssize_t     n;

    if ( (n = readline(fd, ptr, maxlen)) < 0)
        err_sys("readline error");
    return(n);
}

