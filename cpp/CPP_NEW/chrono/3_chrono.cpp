/*
Class time_point. Very simple class
It is nothing but an encapsulation of duration. It holds an object of type duration
*/

#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    time_point<system_clock, seconds>  tp; //default initialisation with duration::zero, ie represents the epoch time of the clock which is the first template parameter.
    cout << tp.time_since_epoch().count() << endl; //time_since_epoch() returns duration object.

    time_point<system_clock, seconds>  tp2(seconds(10)); // construct a time_point at Clock's epoch plus 10 seconds.
    cout << tp2.time_since_epoch().count() << endl;

    cout << time_point<system_clock, seconds>::min().time_since_epoch().count() << endl; // returns a time_point with the smallest possible duration.
    cout << time_point<system_clock, seconds>::max().time_since_epoch().count() << endl; // returns a time_point with the largest possible duration.
    return 0;
}

/*
The class starts to make more sense when used as a nested class like system_clock::time_point
*/
