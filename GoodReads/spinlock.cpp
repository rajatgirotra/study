#include <atomic>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
 
class SpinLock
{
public:
    void lock()
    {
        while(lck.test_and_set(std::memory_order_acquire))
        {}
    }
 
    void unlock()
    {
        lck.clear(std::memory_order_release);
    }
 
private:
    std::atomic_flag lck = ATOMIC_FLAG_INIT;
};

//SpinLock lk;
std::mutex lk;
int count[8] = {0, 0, 0, 0, 0, 0, 0, 0};
 
void foo(int n)
{
    for(unsigned i = 0; i < 10000000; i++)
    {
        lk.lock();
        //while (!lk.try_lock());
        ++count[n];
        lk.unlock();
    }
}
 
int main(int, char**)
{
    std::vector<std::thread> v;
    for(int n = 0; n < 4; ++n)
    {
        v.emplace_back(foo, n);
    }
 
    for (auto& t : v) 
    {
        t.join();
    }
 
    auto x = count[0] + count[1] + count[2] + count[3]
        + count[4] + count[5] + count[6] + count[7];
    cout << x << endl;
}

