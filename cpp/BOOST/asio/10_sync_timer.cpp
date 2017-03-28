/*
This is an async timer.
*/
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <chrono>

using namespace std;

void print(const boost::system::error_code& ec)
{
    cout << "Hello World\n";
}

int main()
{
    //the first thing to do is to create an io_service object. This provides access to
    // I/O functionality.
    boost::asio::io_service io;

    //Create a high resolution time which expires in 5 seconds from current time.
    boost::asio::high_resolution_timer t(io, std::chrono::seconds(5));

    //Instead of calling wait(), call async_wait().
    t.async_wait(&print);

    //You have read already that we need to call run method on io_service object for the
    //completionHandler to be called - in this case the print function.
    io.run();
    //Now this is a blocking call as long as io_service has work to do.
    //Here it is waiting for the async operation to finish.

    return 0;
}

//Have a look at boost asio reference --> timers --> high_resolution_timer help
