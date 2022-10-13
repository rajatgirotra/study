#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
using namespace std;
using boost::asio::ip::tcp;
namespace asio = boost::asio;

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage:\n\tsync_daytime_client <hostname>\n";
        exit (-1);
    }

    asio::io_context io;
    tcp::resolver resolver(io);

    boost::system::error_code ec{};
    auto endpoints = resolver.resolve(argv[1], "13", ec);
    if(ec) {
        cerr << "error [" << (ec.category() == asio::error::system_category ? strerror(ec.value()) : ec.message()) << "] resolving daytime server for host: " << argv[1] << endl;
        exit(-1);
    }
    tcp::socket socket(io);
    cout << "Endpoints\n";
    for(auto iter = endpoints.begin(); iter != endpoints.end(); ++iter) {
        cout << iter->host_name() << "  " << iter->service_name() << " "
        << ", family: " << iter->endpoint().protocol().family() << ", port: " << iter->endpoint().port()
        << ", type: " << iter->endpoint().protocol().type() << endl;
    }
    cout << endl;
    asio::connect(socket, endpoints, ec);
    if(ec) {
        cerr << "error [" << (ec.category() == asio::error::system_category ? strerror(ec.value()) : ec.message()) << "] connecting to host: " << argv[1] << endl;
        exit(-1);
    }

    for(;;) {
        // keep on reading and dumping to cout until the server disconnects.
        boost::array<char, 128> buf{};
        auto len = socket.read_some(asio::buffer(buf), ec);
        if(ec == boost::asio::error::eof) {
            // server disconnected.
            break;
        } else if (ec) {
            cerr << "error [" << (ec.category() == asio::error::system_category ? strerror(ec.value()) : ec.message()) << "] reading from socket" << endl;
            exit(-1);
        }

        std::cout.write(buf.data(), len);
    }
}