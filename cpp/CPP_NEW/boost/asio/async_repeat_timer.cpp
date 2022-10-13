#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
using namespace std;

namespace asio = boost::asio;

void print(const boost::system::error_code& e, asio::steady_timer& timer, int& count) {
    if(count < 5) {
        cout << "Timer count: " << count << endl;
        ++count;
        timer.expires_at(timer.expiry() + asio::chrono::seconds(1));
        timer.async_wait(boost::bind(&print, asio::placeholders::error, std::ref(timer), std::ref(count)));
    }
}
int main() {
    asio::io_context io;
    int count {0};
    asio::steady_timer timer(io, asio::chrono::seconds(1));
    timer.async_wait(boost::bind(&print, asio::placeholders::error, std::ref(timer), std::ref(count)));
    io.run();
}