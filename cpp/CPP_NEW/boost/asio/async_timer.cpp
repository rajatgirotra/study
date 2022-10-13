#include <iostream>
#include <boost/asio.hpp>
using namespace std;
namespace asio = boost::asio;

int main() {
    asio::io_context io;

    asio::steady_timer timer(io, asio::chrono::seconds(5));
    timer.async_wait([](const boost::system::error_code& e) {
       cout << "Timer expired. Hello World\n";
    });

    io.run();
}