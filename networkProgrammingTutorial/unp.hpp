#ifndef _UNP_HPP_
#define _UNP_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctime>
#include <cstdarg>
#include <cstdlib>
#include <cerrno>
#include <cstdio>

#define LISTENQ 1024
#define MAXLINE 4096

#define SA struct sockaddr

#ifdef __cplusplus
extern "C" {
#endif
/*******************  Error related functions  **********************/

    //Non-fatal error related to system call
    //Print error msg and return.
    extern void err_ret(const char* fmt, ...);
    
    //Fatal error related to system call
    //Print error and exit.
    extern void err_sys(const char* fmt, ...);

    //Fatal error related to system call
    //Print error , dump core and terminate.
    extern void err_dump(const char* fmt, ...);

    //Non-fatal error unrelated to system call
    //Print error msg and return.
    extern void err_msg(const char* fmt, ...);

    //Fatal error unrelated to system call
    //Print error and exit.
    extern void err_quit(const char* fmt, ...);
/********************************************************************/


/*******************  Socket related functions  **********************/

    extern int Socket(int family, int type, int protocol);

    extern void Connect(int sockfd, const struct sockaddr* sa, socklen_t len);

    extern void Bind(int sockfd, const struct sockaddr* sa, socklen_t len);

    extern void Listen(int sockfd, int backlog);

    extern int  Accept(int sockfd, sockaddr*, socklen_t*);

    extern void Close(int);

    extern void Write(int sockfd, void* ptr, size_t nBytes);

    extern int  Read(int sockfd, void* ptr, size_t nBytes);

    extern int readn(int fd, void* ptr, size_t n);
    extern int Readn(int fd, void* ptr, size_t n);

    extern int writen(int fd, const void* ptr, size_t n);
    extern void Writen(int fd, const void* ptr, size_t n);

    extern ssize_t readline(int fd, void* ptr, size_t);
    extern ssize_t Readline(int fd, void* ptr, size_t);
/********************************************************************/


/*******************  Input/Output related functions  **********************/
    extern void Fputs(const char* buff, FILE* stream);

    extern char* Fgets(char* str, int n, FILE* stream);

    extern FILE* Fopen(const char* filename, const char* mode);
/********************************************************************/


/*******************  General wrapper functions  **********************/
    extern void Inet_pton(int family, const char* strptr, void* addrptr);

    extern const char* Inet_ntop(int family, const void* addrptr, char* strptr, size_t len);
/********************************************************************/


/*******************  Unix function wrappers  **********************/
    extern pid_t Fork();
/********************************************************************/

#ifdef __cplusplus
}
#endif


#endif // _UNP_HPP_
