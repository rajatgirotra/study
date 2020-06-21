/* Implementing a lock using std::atomic as said in lock_free_23.cpp  */
#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

std::atomic<int> ready(0);

void foo()
{
    for(int i = 0; i < 10000; ++i)
    {
//    asm volatile("mfence" ::: "memory");
        auto x = ready.load(std::memory_order_acquire);
        if (x == 0) {
            cout << "I ";
            std::this_thread::yield();
            cout << "am ";
            std::this_thread::yield();
            cout << "thread ";
            std::this_thread::yield();
            cout << "one \n";
            std::this_thread::yield();
        }
        std::this_thread::yield();
        ready.store(1, std::memory_order_release);
        std::this_thread::yield();
        //   asm volatile("mfence" ::: "memory");
    }
}

void bar()
{
    for(int i = 0; i < 10000; ++i)
    {
        auto x = ready.load(std::memory_order_acquire);
        //   asm volatile("mfence" ::: "memory");
        if (x==1)  {
            std::this_thread::yield();
            cout << "We ";
            std::this_thread::yield();
            cout << "are ";
            std::this_thread::yield();
            cout << "thread ";
            std::this_thread::yield();
            cout << "two \n";
            std::this_thread::yield();
        }
        std::this_thread::yield();
        ready.store(0, std::memory_order_release);
        std::this_thread::yield();
        // asm volatile("mfence" ::: "memory");
    }
}

int main()
{
    std::thread first (foo);
    std::thread second (bar);
    std::cout << "main, foo and bar now execute concurrently...\n";
    first.join();
    second.join();
    std::cout << "foo and bar completed.\n";
    return 0;
}
