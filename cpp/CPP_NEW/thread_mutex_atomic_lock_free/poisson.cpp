#include <iostream>
#include <random>
#include <thread>
#include <chrono>
using namespace std;


double nextTime(double rate)
{
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return -(std::log(1.0f - distribution(generator)))/rate;
}


int main()
{
    double rate = 1.0f/6.0f;

    double sum = 0 ;
    for(int i = 0 ; i < 10; ++i)
    {
        //double d = nextTime(rate);
        //cout << d << endl;
        //sum += d;
        ;
    }
    cout << endl << sum/10 << endl;

    #if 1
    double timer = 0;
    int dt_sec = 1;
    double endInterval = nextTime(rate);
    for(int i = 0; i < 120; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        timer = dt_sec;
        if(timer > endInterval)
        {
            timer = 0;
            endInterval = nextTime(rate); 
            dt_sec = 0;
            cout << "Event at [" << i << "] secs" << endl;
        }
        ++dt_sec;
    }
    #endif
    return 0;
}
    
