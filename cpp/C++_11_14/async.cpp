/*
template <typename Callable,typename... Args>
std::future<result_of<Callable(Args...)>>
std::async(std::launch::async|std::launch::deferred, Callable&& f, Args&&... args)

Very simple
1) If launch policy is std::async, the callable is run immediately on a separate thread.
2) If launch policy is std::deferred, the callable is deferred till the result of the asyn operation is requested from the associated future. Ie when std::future::get() or wait() is called. ALSO THE CALLABLE IS RUN IN THE SAME THREAD WHICH CALLED get() or wait(), which may be different from the thread which called std::async.
3) If no default policy is specified, the default is std::launch::async|std::launch::deferred ie the callable can be run in another thread or can be run in the same thread when get() or wait() is called.
*/

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
using namespace std;


int main() {
    cout << "Main thread id: " << std::this_thread::get_id() << endl;
    std::async(std::launch::async, []() {
        cout << "HelloWorld from another thread with id: " << std::this_thread::get_id() << endl;
        return 100;
    });

    //auto handle = std::async(std::launch::deferred, []() {
    auto handle = std::async([]() {
       cout << "GoodBye cruel world with deferred policy. Thread id: " << std::this_thread::get_id() << endl;
       return 8;
    });
    //handle.get();
    return 0;
}
