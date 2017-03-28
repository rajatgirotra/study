/*
Lets get started with some basic asio tutorials. and we'll learn
more along the way
We start by coding a very simple synchronous timer.
We create a timer object and then wait on it for 5 seconds.
*/
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <chrono>

using namespace std;

int main()
{
    //the first thing to do is to create an io_service object. This provides access to
    // I/O functionality.
    boost::asio::io_service io;

    //Create a high resolution time which expires in 5 seconds from current time.
    boost::asio::high_resolution_timer t(io, std::chrono::seconds(5));

    //Lets block in the wait call.
    t.wait();

    //after the wait, print hello world.
    cout << "Hello World\n";

    return 0;
}

//Have a look at boost asio reference --> timers --> high_resolution_timer help
