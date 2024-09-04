#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
using std::cout;
using std::endl;

// std::promise is much simpler than packaged task. std::promise is an asynchronous provider that holds a shared state.
// It holds the result of the async operation which can be communicated using the std::future object created by this class only.

// case 1, promise created and destroyed.
#if 0
int test() {
   std::promise<int> pr;
   return 0;
} // no problem, promise is created an destroyed, without accessing its std::future object
#endif

// case 2, future created and get() called
#if 0
int test() {
    std::promise<int> pr;
    auto handle = pr.get_future();
    return handle.get();
} // no problem, call to get() will block indefinitely, as the promise is never fulfilled. You need to call set_value() or set_exception() to fulfill the promise.
#endif

// case 3, retrieve future multiple times.
#if 0
int test() {
    std::promise<int> pr; // default constructed promise object has an EMPTY shared state. i.e. shared state exists but is not set to a value or exception.
    auto handle = pr.get_future();
    auto handle2 = pr.get_future(); // can only call get_future() once.
    return 0;
} // exception, std::future_errc::future_already_retrieved
#endif

// case 4, too much satisfaction
#if 0
int test() {
    std::promise<int> pr; /// default constructed promise object has an EMPTY shared state. i.e. shared state exists but is not set to a value or exception.
    pr.set_value(10); // this line throws an exception unexpectedly. It should be the next line. If i compile separately this file, it does not throw exception. May be some compiler flag is causing some weird behavior. Remember that we need -pthread as promise uses thread library.
    pr.set_value(20); // can only set_value() once
    return 0;
} // exception, std::future_errc::promise_already_satisfied.
#endif

// case 5, broken promise
#if 0
int test() {
    std::promise<int> pr;
    auto handle = pr.get_future();
    {
        auto pr2 = std::move(pr); // pr2 gets destroyed.
    }
    return handle.get(); // exception, broken_promise, promise object is destroyed before calling get()
}
#endif

// case 6, promise fulfilled
#if 0
int test() {
    std::promise<int> pr;
    auto handle = pr.get_future();
    {
        auto pr2 = std::move(pr); // pr2 gets destroyed.
        pr2.set_value(10); // it's ok for the promise object to be destroyed after the promise is fulfilled. No need to wait till the future is accessed.
    }
    return handle.get(); // no problem, returns 10
}
#endif

// case 7, promise fulfilled with exception
#if 1
int test() {
    std::promise<int> pr;
    auto handle = pr.get_future();
    {
        auto pr2 = std::move(pr); // pr2 gets destroyed.
        pr2.set_exception(std::make_exception_ptr(std::runtime_error("Booo!!"))); // it's ok for the promise object to be destroyed after the promise is fulfilled. No need to wait till the future is accessed.
    }
    return handle.get(); // no problem, throws std::runtime_error.
}
#endif

int main() {
    try {
        cout <<  test() << endl;
    } catch(const std::future_error& e) {
        cout << "caught future_error: " << e.what() << " , code: " << e.code() << endl;
    } catch(const std::exception& e) {
        cout << "caught std::exception: " << e.what() << endl;
    } catch(...) {
        cout << "unknown exception" << endl;
    }
    return 0;
}
