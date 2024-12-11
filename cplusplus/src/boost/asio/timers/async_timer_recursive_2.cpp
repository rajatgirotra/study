// same as async_timer_recursive.cpp but the timer_callback is class member function.
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

namespace asio = boost::asio;
using namespace std::literals;
using namespace std;

class TimerCallbacks {
private:
    std::shared_ptr<asio::steady_timer> m_timer;
    int m_count{};
public:
    explicit TimerCallbacks(asio::io_context& io, int count = 5) : m_timer(new asio::steady_timer(io)), m_count(count) {
        m_timer->expires_after(1s);
        m_timer->async_wait(std::bind(&TimerCallbacks::callback, std::move(this), asio::placeholders::error, 1));
    }

    void callback(const boost::system::error_code e, int count) {
        if(!e) {
            cout << "Timer expired!" << endl;
            if(count < m_count) {
                m_timer->expires_at(m_timer->expiry() + 1s);
                m_timer->async_wait(std::bind(&TimerCallbacks::callback, std::move(this), asio::placeholders::error, count+1));
            } else {
                cout << "counter reached 5!" << endl;
            }
        } else if(e == asio::error::operation_aborted) {
            cout << "Timer cancelled!" << endl;
        } else {
            cout << "Error: " << e.message() << endl;
        }
    };

    size_t cancel() {
        return m_timer->cancel();
    }
};


int main() {
    asio::io_context io;
    TimerCallbacks tc(io);

    std::jthread t([&io] {
        io.run();
    });

    // wait 3100 millisecs and cancel the timer. it will return the number of async operations that were cancelled.
    // and the CompletionHandler will be invoked immediately with boost::asio::error::operation_aborted
    std::this_thread::sleep_for(3100ms);
//    std::this_thread::sleep_for(5100ms);
    auto count = tc.cancel();
    cout << count << " async operations were cancelled!" << endl;

    return 0;
}