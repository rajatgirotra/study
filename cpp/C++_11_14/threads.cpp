#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
using std::cout;
using std::endl;

// Create a packaged_task to count from a number n down to 1.
// and then return from where you started counting.
struct CountDownThread {
    int operator() (int from, int to) {
        for (auto i = from; i != to; --i) {
            cout << i << endl;
        }
        cout << "Liftoff!" << endl;
        return (from-to);
    }
};

int countdown(int from, int to) {
    for (auto i = from; i != to; --i) {
        cout << i << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "Liftoff!" << endl;
    return (from-to);
}


int main() {
    /* A packaged task has two things:
     1) A task to execute and
     2) A shared state which can be fetched using get_future()"
    */
    std::packaged_task<int(int, int)> tsk(countdown);
    std::future<int> result = tsk.get_future();

    // A thread c'tor can take:
    /*
     a function,
     a pointer to function
     a move assignable function object
     lambda or closures
     Here we pass a move assignable function object
    */
    std::thread th(std::move(tsk), 10, 0);
    th.detach();
    // We can also call the function object in the same thread which makes it synchronous.
    //tsk(10, 0);

    int ret = result.get();
    cout << "The countdown lasted for " << ret << " seconds." << endl;

    return 0;
}
