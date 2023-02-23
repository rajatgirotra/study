#include <iostream>
#include <boost/asio.hpp>
#include <ctime>
#include <string>
#include <thread>
using namespace std;
namespace asio = boost::asio;

string getTime() {
    time_t now{};
    now = std::time(0);
    auto x = ::ctime(&now);
    return string(x);
}

// create a sync timer
int main() {
    asio::io_context io{};

    cout << "time A: " << getTime() << endl;
    asio::steady_timer timer(io, asio::chrono::seconds(10)); // timer starts here already.

    std::this_thread::sleep_for(5s);
    boost::system::error_code ec{};
    try {
        cout << "time B: " << getTime() << endl;
        timer.wait(ec);
    } catch(const boost::system::system_error& e) {
        cerr << "exception during sync timer wait: " << e.what() << ", code: " << e.code() << endl;
    }

    cout << "time C: " << getTime() << endl;
    cout << "Hello World, timer expired\n";
}
