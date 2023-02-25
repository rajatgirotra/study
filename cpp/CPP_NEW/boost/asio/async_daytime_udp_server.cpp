#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <ctime>
using namespace std;
namespace asio = boost::asio;

string getTimeNow() {
    time_t t = time(0);
    auto x = ctime(&t);
    return string(x);
}

class UDPServer {
    asio::io_context& m_io;
    asio::ip::udp::socket m_socket;
    std::array<char, 1> m_buf {{0}};
    asio::ip::udp::endpoint m_remote_endpoint;
public:
    UDPServer(asio::io_context& io) : m_io(io),
    m_socket(m_io, asio::ip::udp::endpoint(asio::ip::udp::v4(), 7777)) {
        start_receive();
    }

    void start_receive() {
        m_socket.async_receive_from(asio::buffer(m_buf), m_remote_endpoint, [this](
                const boost::system::error_code& ec, const size_t len) {
            handle_send();
        });
    }

    void handle_send() {
        string msg = getTimeNow();
        m_socket.async_send_to(asio::buffer(msg), m_remote_endpoint, [this](
                const boost::system::error_code& ec, const size_t len) {
            start_receive();
        });
    }
};

int main() {
    asio::io_context io;
    UDPServer server(io);
    io.run();
}