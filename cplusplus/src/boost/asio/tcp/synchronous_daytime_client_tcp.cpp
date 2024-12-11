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
    // use: time-a-g.nist.gov as the host name

    cout << "Running on host: " << asio::ip::host_name() << endl;

    try {
        // create an io_context
        asio::io_context io;

        // create a resolver object
        asio::ip::tcp::resolver resolver(io);
        auto endpoints = resolver.resolve(argv[1], "daytime");

        // create a socket
        asio::ip::tcp::socket socket(io);
        [[maybe_unused]] auto endpoint = asio::connect(socket, endpoints);

        boost::system::error_code ec;
        while(true) {
            std::array<char, 128> buf;
            // read until eof.
            std::size_t len = socket.read_some(asio::buffer(buf), ec);
            if(ec == asio::error::eof) {
                break;
            } else if(ec) {
                throw boost::system::system_error(ec);
            }
            cout << string_view(buf.data(), len) << endl;
        }
    } catch(const boost::system::error_code& e) {
        cerr << "caught exception: " << e.message() << endl;
    } catch(const std::exception& e) {
        cerr << "caught exception: " << e.what() << endl;
    }
}