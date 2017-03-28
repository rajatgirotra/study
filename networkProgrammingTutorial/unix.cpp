#include "unp.hpp"

pid_t Fork()
{
    pid_t pid;
    if( (pid = fork()) == -1)
        err_sys("fork error");
    return pid;
}
