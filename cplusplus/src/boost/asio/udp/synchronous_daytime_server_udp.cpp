// trivial udp daytime server using synchronous operations.


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


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    cout << "Running on host: " << asio::ip::host_name() << endl;

    try {
        // create an io_context
        asio::io_context io;

        //create a socket and listen on port 3333 and wait for a message from some client
        // socket.open() will be called implicitly by the constructor.
        udp::socket socket(io, udp::endpoint(udp::v4(), 3333));

        while(true) {
            udp::endpoint sender_endpoint;
            std::array<char, 1> buf{};
            socket.receive_from(asio::buffer(buf), sender_endpoint);

            boost::system::error_code ignored_error;
            auto message = make_daytime_string();
            socket.send_to(asio::buffer(message), sender_endpoint, 0, ignored_error);
        }
    } catch(const boost::system::error_code& e) {
        cerr << "caught exception: " << e.message() << endl;
    } catch(const std::exception& e) {
        cerr << "caught exception: " << e.what() << endl;
    }
}


