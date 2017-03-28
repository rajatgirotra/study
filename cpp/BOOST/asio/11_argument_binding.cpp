/*
This is an async timer.
But here we want the timer to run every second for 5 seconds and then the program should exit.
This example will also show how to bind arguments to the completion handler. You might
know this already (using boost::bind or std::bind)
*/
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <chrono>
#include <boost/bind.hpp>

using namespace std;

void print(const boost::system::error_code& ec,
           boost::asio::high_resolution_timer* timer,
           int* count)
{
    if(*count < 5)
    {
        cout << "Hello World, count = " << *count << endl;
        ++(*count);
        timer->expires_at(timer->expires_at() + std::chrono::seconds(1));
        timer->async_wait(boost::bind(&print, boost::asio::placeholders::error,
                                 timer, count));
    }
}

int main()
{
    //the first thing to do is to create an io_service object. This provides access to
    // I/O functionality.
    boost::asio::io_service io;

    int count = 0;

    //Create a high resolution time which expires in 5 seconds from current time.
    boost::asio::high_resolution_timer t(io, std::chrono::seconds(1));

    //Instead of calling wait(), call async_wait().
    t.async_wait(boost::bind(&print,
                             boost::asio::placeholders::error, //placeholder for boost::system::error_code
                             &t,
                             &count));

    //You have read already that we need to call run method on io_service object for the
    //completionHandler to be called - in this case the print function.
    io.run();
    //Now this is a blocking call as long as io_service has work to do.
    //Here it is waiting for the async operation to finish.

    cout << "Final count : " << count << endl;
      
    return 0;
}

//Have a look at boost asio reference --> timers --> high_resolution_timer help
