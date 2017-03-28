#include "unp.hpp"

void Fputs(const char* buff, FILE* stream)
{
    if(fputs(buff, stream) == EOF)
        err_sys("fputs error");
}

char* Fgets(char* str, int n, FILE* stream)
{
    char* chPtr;

    if(((chPtr = fgets(str, n, stream)) == 0) && ferror(stream))
        err_sys("fgets error");

    return chPtr;
}

FILE* Fopen(const char* filename, const char* mode)
{
    FILE* fd;
    fd = fopen(filename, mode);
    if(fd == 0)
        err_sys("fopen error");

    return fd;
}
