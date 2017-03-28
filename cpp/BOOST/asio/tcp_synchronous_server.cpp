#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <ctime>

using std::string;
using std::cout;
using std::endl;
namespace asio = boost::asio;

string get_time() {
    time_t rawtime;
    struct tm* tminfo;
    time(&rawtime);
    tminfo = localtime(&rawtime);
    return string(asctime(tminfo));
}
int main(int argc, char* argv[]) {
    // create an io_service
    asio::io_service service;

    // create a tcp acceptor
    asio::ip::tcp::acceptor acceptor(service, asio::ip::tcp::endpoint(
                                         asio::ip::tcp::v4(), 7777));

    // Listen for connections
    while (true) {
        asio::ip::tcp::socket socket(service);
        acceptor.accept(socket); // socket is the connected socket.
        boost::system::error_code ec;
        string t = get_time();
        asio::write(socket, asio::buffer(t.data(), t.size()));
    }
}
