#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
using std::cout;
using std::endl;

// std::promise is much simple than packaged task. std::promise is an asymchronous provider that holds a shared state. It holds the result of the async operation which can be communicated using the std::future object created by this class only.

// case 1, promise created and destroyed.
#if 0
int test() {
   std::promise<int> pr;
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
    std::promise<int> pr;
    auto handle = pr.get_future();
    auto handle2 = pr.get_future(); // can only call get_future() once.
} // exception, std::future_errc::future_already_retrieved
#endif

// case 4, too much satisfaction
#if 0
int test() {
    std::promise<int> pr;
    pr.set_value(10);
    pr.set_value(20); // can only set_value() once
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
        pr2.set_value(10); // its ok for the promise object to be destroyed after the promise is fulfilled. No need to wait till the future is accessed.
    }
    return handle.get(); // no problem, returns 10
}
#endif

// case 6, promise fulfilled with exception
#if 1
int test() {
    std::promise<int> pr;
    auto handle = pr.get_future();
    {
        auto pr2 = std::move(pr); // pr2 gets destroyed.
        pr2.set_exception(std::make_exception_ptr(std::runtime_error("Booo!!"))); // its ok for the promise object to be destroyed after the promise is fulfilled. No need to wait till the future is accessed.
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
        cout << "caugh std::exception: " << e.what() << endl;
    } catch(...) {
        cout << "unknown exception" << endl;
    }
    return 0;
}
