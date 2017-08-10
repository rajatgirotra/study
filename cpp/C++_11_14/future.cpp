/*
std::future is used to fetch the result of an asynchronous operation. The asynchronous providers are std::async, std::promise or std::packaged_task. These providers may either set a value or an exception that can be retrieved by the future object. The future object reference a shared state of the asynchronous provider.

Let's look at the std::future API.

1) default c'tor
2) move c'tor
3) bool valid() --> returns if the std::future object is valid or not. A default constructed object and the moved from object are invalid. A future is valid if

a) It was created from std::async, std::promise or std::packaged_task and
b) It was valid till the first call to the get() function. after you retrieve the result of the asynchronous operation, the future becomes invalid. Most future operations API's have undefined behaviore if valid()==false before the call.

4) get() --> blocks till the result of asynchronous operation is available.
5) wait() --> blocks
6) std::future_status wait_for()
7) std::future_status wait_until()
std::future_status can be
a) deferred: meaning the async task hasn't begin operation
b) ready: the result is available.
c) timeout: the operation expired.

8) std::shared_future share() --> to convert an std::future to std::shared_future object. valid() == false after the call.

Since get() can throw an exception too, also surround it in a try-catch block.
Let's see it in action.
*/

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <chrono>
#include <vector>
using namespace std;

int main() {
    auto handle = std::async(std::launch::async, []() {
        cout << "Hello World from another thread" << endl;
        return 100;
    });

    cout << handle.get() << endl; // will return 100
    return 0;
}

