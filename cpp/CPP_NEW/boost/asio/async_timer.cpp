#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <ctime>
using namespace std;
namespace asio = boost::asio;

int main() {
    asio::io_context io;
    asio::steady_timer timer(io, asio::chrono::seconds(5));

    timer.async_wait([](const boost::system::error_code& ec) {
        cout << "Hello World, timer expired\n";
    });

    io.run();
}