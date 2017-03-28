/*
Different types of clocks
*/
#include <iostream>
#include <ctime>
#include <cerrno>
#include <iomanip>
#include <sys/time.h>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Clock times " << endl;
    cout << "\t\t\t\tseconds\t\tnanoseconds" << endl;
    struct timespec ts;    
    int success = clock_gettime(CLOCK_REALTIME, &ts);
    if(success == 0) {
        cout << "CLOCK_REALTIME\t\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_gettime() failed with error: " << success << endl;
    }

    success = clock_gettime(CLOCK_REALTIME_COARSE, &ts);
    if(success == 0) {
        cout << "CLOCK_REALTIME_COARSE\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_gettime() failed with error: " << success << endl;
    }

    success = clock_gettime(CLOCK_MONOTONIC, &ts);
    if(success == 0) {
        cout << "CLOCK_MONOTONIC\t\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_gettime() failed with error: " << success << endl;
    }

    success = clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    if(success == 0) {
        cout << "CLOCK_MONOTONIC_RAW\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_gettime() failed with error: " << success << endl;
    }
    
    success = clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
    if(success == 0) {
        cout << "CLOCK_MONOTONIC_COARSE\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_gettime() failed with error: " << success << endl;
    }

    success = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    if(success == 0) {
        cout << "CLOCK_PROCESS_CPUTIME_ID\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_gettime() failed with error: " << success << endl;
    }

    success = clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
    if(success == 0) {
        cout << "CLOCK_THREAD_CPUTIME_ID\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_gettime() failed with error: " << success << endl;
    }

    struct timeval timev;
    success = gettimeofday(&timev, 0);
    if(success == 0)
    {
        cout << "GET_TIMEOF_DAY\t\t\t" << timev.tv_sec << "\t\t" << timev.tv_usec << endl;
    }
    
    clockid_t clockId;
    //Returns the CPU Clock id of the process whose pid is given as first argument
    success = clock_getcpuclockid(1, &clockId);
    if(success == 0) {
        cout << "clock_getcpuclockid of init process returned: " << clockId << endl;
    }
    else
    {
        cerr << "clock_getcpuclockid failed with error: " << success << endl;
    }

    
    success = clock_getcpuclockid(0, &clockId);
    if(success == 0) {
        cout << "clock_getcpuclockid of this process returned: " << clockId << endl;
    }
    else
    {
        cerr << "clock_getcpuclockid failed with error: " << success << endl;
    }

    return 0;
}
