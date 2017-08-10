/*
Very simple concept, Create an instance of std::once_flag. Then you can call 

template <typename Callable, typename... Args>
std::call_once(std::once_flag& once, Callable&& c, Args&&... args) multiple times, but the API will guarantee that only one of the callables is selected and called. If that callable throws an exception, the exception will be returned to the caller and another callable will be choosen.

Lets see it in action. This example does not work yet as the program hangs after an exception is thrown by call_once
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <exception>
#include <vector>
#include <chrono>
using namespace std;

std::once_flag flag1, flag2;

void simple_do_once() {
    std::call_once(flag1, []() {
        cout << "Simple do once\n" << endl;
    });
}

void may_throw_function(bool do_throw) {
    if(do_throw) {
        cout << "may throw function throwing exception\n";
        throw std::exception();
    }
    cout << "may throw function called once\n";
}

void do_once(bool do_throw) {
    cout << "In do_once" << endl;
    try {
        std::call_once(flag2, may_throw_function, do_throw);
    } catch(...) {}
}

int main() {
    vector<std::thread> thList;
    for (auto i = 0; i < 4; ++i) {
        thList.push_back(std::thread(simple_do_once));
    }

    std::thread st2(do_once, true); 
    std::thread st1(do_once, false);
    
    cout << "A\n";

    for(auto& t: thList)
        t.join();

    cout << "B\n";
    st1.join(); 
    st2.join();

    cout << "C\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}

