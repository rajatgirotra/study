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
public:
    UDPServer(asio::io_context& io) : m_io(io) {
        start();
    }

    void start() {
        asio::ip::udp::socket socket(m_io, asio::ip::udp::endpoint(asio::ip::udp::v4(), 7777));
        try {
            for(;;) {
                asio::ip::udp::endpoint remote_endpoint;
                std::array<char, 1> buf;
                boost::system::error_code ec{};
                size_t len = socket.receive_from(asio::buffer(buf), remote_endpoint);
                cout << "received message with " << len << " byte(s)\n";
                if(len > 0) {
                    string msg = getTimeNow();
                    socket.send_to(asio::buffer(msg), remote_endpoint, 0, ec);
                }
            }
        } catch(const std::exception& e) {
            cout << "caught exception: " << e.what() << endl;
        }
    }
};

int main() {
    asio::io_context io;
    UDPServer server(io);
}