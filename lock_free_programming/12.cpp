/* Fix as you said in 3_Must_Read.txt last line */


#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

std::atomic<int> ready(0);

void foo()
{
    for(int i = 0; i < 10000; ++i)
    {
    asm volatile("mfence" ::: "memory");
    ready.load(std::memory_order_acquire);
    cout << "I ";
    cout << "am ";
    cout << "thread ";
    cout << "one \n";
    std::this_thread::yield();
    ready.store(1, std::memory_order_release);
/   asm volatile("mfence" ::: "memory");
    }
}

void bar()
{
    for(int i = 0; i < 10000; ++i)
    {
    ready.load(std::memory_order_acquire);
 //   asm volatile("mfence" ::: "memory");
    cout << "We ";
    cout << "are ";
    cout << "thread ";
    cout << "two \n";
    std::this_thread::yield();
    ready.store(1, std::memory_order_release);
   // asm volatile("mfence" ::: "memory");
    }
}

int main()
{
    std::thread first (foo);
    std::thread second (bar);


    std::cout << "main, foo and bar now execute concurrently...\n";
    

    first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}
