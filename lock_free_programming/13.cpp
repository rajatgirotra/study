#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <pthread.h>

std::mutex mtx;
pthread_mutex_t pmtx;
using namespace std;
using namespace std::chrono;

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;


void thread_lock_unlock_test()
{
    Clock::time_point tp = Clock::now();
    for(int i = 0; i < 1000000; ++i)
    {
        //std::lock_guard<std::mutex> lck(mtx);
        //mtx.lock(); mtx.unlock();
        pthread_mutex_lock(&pmtx);  pthread_mutex_unlock(&pmtx);
    }
    Clock::time_point tp2 = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(tp2 - tp);
    cout << "millisec: " << ms.count() << endl;
} 

int main()
{

    std::thread t(thread_lock_unlock_test);
    t.join();

    return 0;
}
 
