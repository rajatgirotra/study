// async timers can be cancelled.
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

namespace asio = boost::asio;
using namespace std::literals;
using namespace std;

int main() {

    asio::io_context io;
    auto timer = std::make_shared<asio::steady_timer>(io, 5s);

    boost::system::error_code ec;

    // async wait
    timer->async_wait([&](boost::system::error_code e) {
        if(!e) {
            cout << "Timer expired!" << endl;
        } else if(e == asio::error::operation_aborted) {
            cout << "Timer cancelled!" << endl;
        } else {
            cout << "Error: " << e.message() << endl;
        }
    });

    timer->async_wait([&](boost::system::error_code) {
        cout << "Second async wait on the same timer!" << endl;
    });

    std::jthread t([&io] {
        io.run();
    });

    // wait 1 second and cancel the timer. It will return the number of async operations that were cancelled.
    // and the CompletionHandler will be invoked immediately with boost::asio::error::operation_aborted
    std::this_thread::sleep_for(1s);
    auto count = timer->cancel();
    cout << count << " async operations were cancelled!" << endl;

    return 0;
}