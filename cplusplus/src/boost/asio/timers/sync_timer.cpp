#include <boost/asio.hpp>
#include <iostream>
#include <thread>

namespace asio = boost::asio;
using namespace std::literals;
using namespace std;

int main() {

    asio::io_context io;
    asio::steady_timer timer{io, 5s};

    boost::system::error_code ec;

    timer.wait(ec); // synchronous wait, no native api of easy way to cancel/interrupt this.

    if(!ec) {
        cout << "Timer expired!" << endl;
    } else {
        cout << "Error: " << ec.message() << endl;
    }
    return 0;
}