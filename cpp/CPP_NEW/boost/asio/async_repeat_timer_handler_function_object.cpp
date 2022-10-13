#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
using namespace std;

namespace asio = boost::asio;

struct printer {
private:
    asio::steady_timer m_timer;
    int m_count{0};

public:
    explicit printer(asio::io_context& io) : m_timer(io, asio::chrono::seconds(1)) {
        m_timer.async_wait(boost::bind(&printer::print, this));
    }

    void print() {
        if(m_count < 5) {
            cout << "Timer count " << m_count << endl;
            ++m_count;
            m_timer.expires_at(m_timer.expiry() + asio::chrono::seconds(1));
            m_timer.async_wait(boost::bind(&printer::print, this));
        }
    }
};

int main() {
    asio::io_context io;
    printer p(io);
    io.run();
}