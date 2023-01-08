/*
std::jthread: j just means joinable i.e. the destructor of jthread will call join() to wait for thread to finish.
std::thread doesn't do this. so it is not an RAII type. with std::thread you must explicitly call join() or detach().
otherwise your program will call terminate(). This led to problems when after creating the thread and before calling
join(), your code threw exception. in that case join() was not called. so std::thread was not exception safe.
you had to wrap all the code after a thread creation into a try..catch block and handle exceptions explicitly.
*/
#include <thread> // jthread and thread are in the same namespace and header for ease of migration
#include <string>
#include <iostream>
using namespace std;

int main() {
    std::jthread t([]() {
        cout << "From inside a thread\n";
    });

    // no need to call t.join()
//    t.join();
}