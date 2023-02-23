#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <functional>
using namespace std;
namespace asio = boost::asio;

void print(asio::steady_timer& timer, int& count, const boost::system::error_code& ec) {
    if(count < 5) {
        cout << "Timer expired, count: " << count + 1 << endl;
        ++count;
        timer.expires_at(timer.expiry() + asio::chrono::seconds(1));
        timer.async_wait(boost::bind(&print, std::ref(timer), std::ref(count), asio::placeholders::error));
    }
}

int main() {
    asio::io_context io;
    asio::steady_timer timer(io, asio::chrono::seconds(1));
    int count{};

    timer.async_wait(boost::bind(&print, std::ref(timer), std::ref(count), asio::placeholders::error));

    io.run();
}
