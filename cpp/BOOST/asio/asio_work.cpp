#include <boost/asio/io_service.hpp>
#include <iostream>
#include <chrono>
#include <thread>

using std::cout;
using std::endl;

int main() {
    boost::asio::io_service service;
    // We create a work class object specifying the io_service in the
    // c'tor. This way the run() function will not return even if there are
    // no active handlers to execute.
    std::shared_ptr<boost::asio::io_service::work>
        wrk_ptr(new boost::asio::io_service::work(service));

    // wrk_ptr.reset();

    std::thread dispatch_thread([&]() {
        // sleep on this thread to prove that asio.run() does not return.
        // and then post something to the service.
        std::this_thread::sleep_for(std::chrono::seconds(3));
        wrk_ptr->get_io_service().post([]() {
                cout << "Hello Asio. I am from the dispatch thread" << endl;
            });
        // destroy the work object so the run() function can unblock.
        wrk_ptr.reset();
    });

    service.run();  // Will not return
    dispatch_thread.join();
    return 0;
}
