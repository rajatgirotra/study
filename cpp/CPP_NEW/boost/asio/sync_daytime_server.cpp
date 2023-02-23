#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <ctime>
using namespace std;
namespace asio = boost::asio;

string getTimeNow() {
    time_t t = time(0);
    auto x = std::ctime(&t);
    return string(x);
}

int main() {
    //1. create io context
    asio::io_context io;

    //2. create tcp acceptor at local port 7777
    asio::ip::tcp::acceptor acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 7777));

    //3. in a for loop, start processing connections.
    try {
        for(;;) {

            //4. accept connection
            asio::ip::tcp::socket socket(io);
            acceptor.accept(socket);

            cout << "a client connected, local ip & port: (" << socket.local_endpoint().address().to_string() << ", " << socket.local_endpoint().port()
                 << "), remote ip & port: (" << socket.remote_endpoint().address().to_string() << ", " << socket.remote_endpoint().port() << ")\n";


            //5. write date time and exit.
            boost::system::error_code ec{};
            boost::asio::write(socket, asio::buffer(getTimeNow()), ec); // ignore error for now

        }
    } catch(const std::exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }

}