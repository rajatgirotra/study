// trivial daytime client using synchronous operations.
// accepts a host name as argument which is resolved to an IP address.

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <array>
#include <string_view>

using namespace std;
namespace asio = boost::asio;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cerr << "Usage: " << argv[0] << " <hostName>" << endl;
        return 1;
    }
    // use: time.nist.gov as the host name

    cout << "Running on host: " << asio::ip::host_name() << endl;

    try {
        // create an io_context
        asio::io_context io;

        // no connection required for udp. Just resolve the udp endpoint and send a message and wait for response.
        asio::ip::udp::resolver resolver(io);
//        auto endpoints = resolver.resolve(asio::ip::udp::v4(), argv[1], "daytime");
        auto endpoints = resolver.resolve(asio::ip::udp::v4(), "localhost", "4444");
        auto remote_endpoint = endpoints.begin()->endpoint();
//        cout << "remote endpoint: " << remote_endpoint <<  "  " << remote_endpoint.port() << endl;

        std::array<char, 1> buf {{0}};
        asio::ip::udp::socket socket(io);
        socket.open(asio::ip::udp::v4());
        socket.send_to(asio::buffer(buf), remote_endpoint);

//        cout << "sent\n";
        // wait for response back
        std::array<char, 128> response_buffer {{0}};
        asio::ip::udp::endpoint sender_endpoint{};
        std::size_t len = socket.receive_from(asio::buffer(response_buffer), sender_endpoint);
//        cout << "received\n";
        cout << string_view(response_buffer.data(), len) << endl;
    } catch(const boost::system::error_code& e) {
        cerr << "caught exception: " << e.message() << endl;
    } catch(const std::exception& e) {
        cerr << "caught exception: " << e.what() << endl;
    }
}
