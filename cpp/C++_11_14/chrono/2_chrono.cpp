#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    typedef duration<int> seconds_type;
    typedef duration<int, std::milli> millseconds_type;
    typedef duration<int, ratio<60*60, 1>> hours_type;
    typedef duration<double, ratio<60*60, 1>> real_hours_type; //supports fractional hours.

    seconds_type sec(3600); //is ok because 3600 is nothing but int, the first template parameter of seconds_type
    hours_type hrs(3); //is ok for same reason
    //hours_type hrs2(3.5) ; //will not compile because assigning 3.5 to int will cause truncation.
    real_hours_type real_hrs(3.5);

    //add 15 more seconds to sec
    sec += seconds(15);
    cout << sec.count() << endl;

    //Assign 115 seconds to hrs
    //hrs = sec; //will not compile because the target type has less precision than the source.
               // will need to use duration_cast<> explicitly
    hrs = duration_cast<hours_type>(sec);
    cout << hrs.count() << endl;

    millseconds_type mil (sec); //is allowed because the target type milliseconds is more specific or precise than source type sec.
    cout << mil.count() << endl;

    //However this is allowed
    real_hours_type real_hrs2(sec); //this is because real_hours_type first template parameter is a double, so it will be assigned a fractional value.
    cout << real_hrs2.count() << endl;

//    seconds_type sec2(real_hrs2); //now the reverse is not possible as the source type is double and target is int. so use duration_cast
    seconds_type sec2 = duration_cast<seconds_type>(real_hrs2);
    cout << sec2.count() << endl;
    return 0;
}

/*
If you look into the header chrono and look at the constructor's of duration class, you'll see how beautifully they have designed it.
If you do

millseconds_type mil(sec); then it finds out if the assignment is ok by calculating

ratio_divide<seconds_type Period2, millseconds_type Period1>::den == 1

You can test out yourself. seconds period is ratio<1,1> and millseconds_type period is ratio<1,1000>

so 1/1 / 1/1000, denominator will be 1.
This will be true for all valid conversions which do not cause truncation. For others it will be false

*/
