#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <boost/bind/bind.hpp>
using namespace std;
namespace asio = boost::asio;

struct Printer {
    asio::io_context& m_io;
    asio::steady_timer m_timer;
    int m_count {};

    Printer(asio::io_context& io) : m_io(io), m_timer(m_io, asio::chrono::seconds(1)), m_count(0) {
        m_timer.async_wait(boost::bind(&Printer::print, this, asio::placeholders::error));
    }

    void print(const boost::system::error_code& ec) {
        if(m_count < 5) {
            cout << "Timer expired, count: " << m_count << endl;
            ++m_count;
            m_timer.expires_at(m_timer.expiry() + asio::chrono::seconds(1));
            m_timer.async_wait(boost::bind(&Printer::print, this, asio::placeholders::error));
        }
    }
};

int main() {
    asio::io_context io;
    Printer p(io);
    io.run();
}
