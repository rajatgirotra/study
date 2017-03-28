#include "unp.hpp"

static void err_doIt(int errnoFlag, const char* fmt, va_list);


void err_ret(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    err_doIt(1, fmt, ap);

    va_end(ap);
    return;
}


void err_sys(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    err_doIt(1, fmt, ap);

    va_end(ap);

    //Exit now
    exit(1);
}


void err_dump(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    err_doIt(1, fmt, ap);

    va_end(ap);

    //Abort. This produces a core dump.
    abort();
}

void err_msg(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    err_doIt(0, fmt, ap);

    va_end(ap);
    return;
}

void err_quit(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    err_doIt(0, fmt, ap);

    va_end(ap);
    exit(1);
}

void err_doIt(int errnoFlag, const char* fmt, va_list ap)
{
    int errno_save, n;
    char buff[MAXLINE + 1];

    errno_save = errno;

    vsnprintf(buff, MAXLINE, fmt, ap);

    n = strlen(buff);

    if(errnoFlag)
        snprintf(buff + n, MAXLINE - n, ": %s", strerror(errno_save));

    strcat(buff, "\n");

    fflush(stdout);
    fputs(buff, stderr);
    fflush(stderr);
    return;
}
