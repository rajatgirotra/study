// trivial udp daytime server using asynchronous operations.

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <array>
#include <string_view>

using namespace std;
namespace asio = boost::asio;
using udp = asio::ip::udp;

string make_daytime_string() {
    time_t now = time(0);
    return ctime(&now);
}

class UDPServer : public std::enable_shared_from_this<UDPServer> {
private:
    asio::io_context& m_io;
    udp::socket m_socket;
    udp::endpoint m_remote_endpoint{};
public:
    explicit UDPServer(asio::io_context& io) : m_io(io), m_socket(m_io, udp::endpoint(udp::v4(), 4444)) {}

    void run() {
        receive();
    }

    void receive() {
        std::array<char, 1> buf{};
        m_socket.async_receive_from(asio::buffer(buf), m_remote_endpoint, [self = shared_from_this()] (const boost::system::error_code ec,
                size_t) {
            if(!ec) {
                self->send();
                self->receive();
            }
        });
    }

    void send() {
        auto message = make_daytime_string();
        m_socket.async_send_to(asio::buffer(message), m_remote_endpoint, [self = shared_from_this()] (const boost::system::error_code,
                                                                                                    size_t) {

        });
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    cout << "Running on host: " << asio::ip::host_name() << endl;

    try {
        // create an io_context
        asio::io_context io;
        std::make_shared<UDPServer>(io)->run();
        io.run();
    } catch(const boost::system::error_code& e) {
        cerr << "caught exception: " << e.message() << endl;
    } catch(const std::exception& e) {
        cerr << "caught exception: " << e.what() << endl;
    }
}


