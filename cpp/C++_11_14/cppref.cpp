#include <iostream>
#include <thread>
#include <mutex>
 
std::once_flag flag1, flag2;
 
void simple_do_once()
{
    std::call_once(flag1, [](){ std::cout << "Simple example: called once\n"; });
}
 
void may_throw_function(bool do_throw)
{
  if (do_throw) {
    std::cout << "throw: call_once will retry\n"; // this may appear more than once
    throw std::exception();
  }
  std::cout << "Didn't throw, call_once will not attempt again\n"; // guaranteed once
}
 
void do_once(bool do_throw)
{
  try {
    std::call_once(flag2, may_throw_function, do_throw);
  }
  catch (...) {
  }
}
 
int main()
{
    std::thread st1(simple_do_once);
    std::thread st2(simple_do_once);
    std::thread st3(simple_do_once);
    std::thread st4(simple_do_once);
    st1.join();
    st2.join();
    st3.join();
    st4.join();
 
    std::thread t1(do_once, true); // Important. The standard says that if a callable throws an exception, then it will not return and another callable will be choosen to run. Now here, most of the times, the thread t1 gets scheduled immediately which throws an exception, so thread t2, t3, t4 never get a chance to get started and the program hange forever.
    std::thread t2(do_once, true);
    std::thread t3(do_once, false);
    std::thread t4(do_once, true);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
