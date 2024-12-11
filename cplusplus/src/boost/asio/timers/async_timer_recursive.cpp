// create an async timer which expires every second until cancelled.
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

namespace asio = boost::asio;
using namespace std::literals;
using namespace std;

void timer_callback(const boost::system::error_code e, std::shared_ptr<asio::steady_timer> timer, int count) {
    if(!e) {
        cout << "Timer expired!" << endl;
        if(count < 5) {
            timer->expires_at(timer->expiry() + 1s);
            timer->async_wait(std::bind(timer_callback, asio::placeholders::error, timer, count+1));
        } else {
            cout << "counter reached 5!" << endl;
        }
    } else if(e == asio::error::operation_aborted) {
        cout << "Timer cancelled!" << endl;
    } else {
        cout << "Error: " << e.message() << endl;
    }
};

int main() {

    asio::io_context io;
    auto timer = std::make_shared<asio::steady_timer>(io);

    boost::system::error_code ec;

    timer->expires_after(1s);
    timer->async_wait(std::bind(timer_callback, asio::placeholders::error, timer, 1));

    std::jthread t([&io] {
        io.run();
    });

    // wait 3100 millisecs and cancel the timer. it will return the number of async operations that were cancelled.
    // and the CompletionHandler will be invoked immediately with boost::asio::error::operation_aborted
    std::this_thread::sleep_for(3100ms);
    auto count = timer->cancel();
    cout << count << " async operations were cancelled!" << endl;
    return 0;
}