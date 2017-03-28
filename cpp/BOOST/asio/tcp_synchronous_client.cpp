#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string>

using std::cout;
using std::endl;
using std::string;
namespace asio = boost::asio;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage:\n\t" << argv[0] << " <host>" << endl;
        return -1;
    }
    asio::io_service service;
    // Create a TCP address resolver
    asio::ip::tcp::resolver resolver(service);

    // Create a query
    // asio::ip::tcp::resolver::query query(asio::ip::tcp::v4(),
    //                                      argv[1], "daytime");

    asio::ip::tcp::resolver::query query(asio::ip::tcp::v4(),
                                         argv[1], "7777",
                                         asio::ip::tcp::resolver::query::numeric_service);

    boost::system::error_code ec;
    auto iterator = resolver.resolve(query, ec);
    if (ec) {
        cout << "Error during query resolver " << ec.message() << endl;
        return -1;
    }

    asio::ip::tcp::socket socket(service);
    asio::connect(socket, iterator);

    while (true) {
        boost::array<char, 256> buf{};
        size_t len = socket.read_some(boost::asio::buffer(buf), ec);
        if (ec == boost::asio::error::eof)
            break;
        else if(ec) {
            throw boost::system::system_error(ec);
        }
        cout.write(buf.data(), len);
    }
    return 0;
}
