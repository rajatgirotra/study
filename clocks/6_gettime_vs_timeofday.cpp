/*
We do an experient here.
We call both gettime and gettimeofday 1mio times and then use perf to see
where the time is spent. For clock_gettime  all time should be in kernel space
and for gettimeofday all time should be in user space (in the vdso) library

Because we will use perf, compile with -g -fno-omit-frame-pointer
*/

#include <iostream>
#include <ctime> //for clock_gettime
#include <sys/time.h> //for gettimeofday

using namespace std;
int main()
{
    struct timespec ts;
    struct timeval tv;

    for(auto i = 0; i < 1000000; ++i)
    {
        clock_gettime(CLOCK_REALTIME, &ts);
        //gettimeofday(&tv, 0);
    }

    return 0;
}
