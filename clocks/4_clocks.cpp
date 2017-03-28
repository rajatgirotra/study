/*
Different types of clocks
*/
#include <iostream>
#include <ctime>
#include <cerrno>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Clock resolutions " << endl;
    cout << "\t\t\t\tseconds\t\tnanoseconds" << endl;
    struct timespec ts;    
    int success = clock_getres(CLOCK_REALTIME, &ts);
    if(success == 0) {
        cout << "CLOCK_REALTIME\t\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_getres() failed with error: " << success << endl;
    }

    success = clock_getres(CLOCK_REALTIME_COARSE, &ts);
    if(success == 0) {
        cout << "CLOCK_REALTIME_COARSE\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_getres() failed with error: " << success << endl;
    }

    success = clock_getres(CLOCK_MONOTONIC, &ts);
    if(success == 0) {
        cout << "CLOCK_MONOTONIC\t\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_getres() failed with error: " << success << endl;
    }

    success = clock_getres(CLOCK_MONOTONIC_RAW, &ts);
    if(success == 0) {
        cout << "CLOCK_MONOTONIC_RAW\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_getres() failed with error: " << success << endl;
    }
    
    success = clock_getres(CLOCK_MONOTONIC_COARSE, &ts);
    if(success == 0) {
        cout << "CLOCK_MONOTONIC_COARSE\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_getres() failed with error: " << success << endl;
    }

    success = clock_getres(CLOCK_PROCESS_CPUTIME_ID, &ts);
    if(success == 0) {
        cout << "CLOCK_PROCESS_CPUTIME_ID\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_getres() failed with error: " << success << endl;
    }

    success = clock_getres(CLOCK_THREAD_CPUTIME_ID, &ts);
    if(success == 0) {
        cout << "CLOCK_THREAD_CPUTIME_ID\t\t " <<  ts.tv_sec << "\t\t" << ts.tv_nsec << endl;
    }
    else
    {
        cerr << "clock_getres() failed with error: " << success << endl;
    }
    /*
     * On my ubuntu DELL XPS 13 Intel Core i7 2Ghz processor, all resoolutions are 1 nanoseconds
       Looks like all these clocks are using the TSC hardware counter
    */

    return 0;
}
