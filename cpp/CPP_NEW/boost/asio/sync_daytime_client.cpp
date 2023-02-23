#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <array>
#include <algorithm>
using namespace std;
namespace asio = boost::asio;

int main(int argc, char** argv) {

    if(argc != 2) {
        cout << "Usage:\n\t" << argv[0] << " <Host>\n";
        return -1;
    }

    //1. create io_context
    asio::io_context io{};

    //2. create a tcp resolver
    asio::ip::tcp::resolver resolver(io);

    //3. resolve all possible endpoints
//    auto endpoints = resolver.resolve(argv[1], "daytime");
    auto endpoints = resolver.resolve("", "7777"); // empty hostname means localhost

    // print endpoints for fun
    std::for_each(endpoints.begin(), endpoints.end(), [](const asio::ip::basic_resolver_entry<asio::ip::tcp>& entry) {
        cout << "Endpoint, host_name: " << entry.host_name() << ", service_name: " << entry.service_name() << ", address: " << entry.endpoint().address().to_string()
             << ", port: " << entry.endpoint().port() << endl;
    });

    //4.create a tcp::socket, and try connecting to endpoints one at a time until you successfully connect
    asio::ip::tcp::socket socket(io);
    asio::connect(socket, endpoints);

    cout << "connection established, local ip & port: (" << socket.local_endpoint().address().to_string() << ", " << socket.local_endpoint().port()
         << "), remote ip & port: (" << socket.remote_endpoint().address().to_string() << ", " << socket.remote_endpoint().port() << ")\n";

    //5. continuously receive TCP stream of bytes until the server closes the connection
    try {
        for(;;) {
            std::array<char, 128> buffer{};
            boost::system::error_code ec{};
            auto len = socket.read_some(asio::buffer(buffer), ec);
            if(ec == asio::error::eof) {
                cout << "EOF\n";
                break;
            } else if(ec) {
                throw boost::system::system_error(ec);
            }
            cout.write(buffer.data(), len);
        }
    } catch(const boost::exception& e) {
        cerr << "Exception caught: \n";
    }

}
