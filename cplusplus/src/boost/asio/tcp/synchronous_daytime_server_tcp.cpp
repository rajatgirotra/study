/*
 * In Boost.Asio, the ip::basic_resolver class template resolves a query to a list of remote endpoints. When you create a query with a hostname and service
 * (like "www.example.com" and "http"), basic_resolver contacts a DNS service (either a local or remote DNS server configured in the system) to translate that
 * hostname to a list of remote IP addresses and ports that can be used to connect to the specified service.
 *
 * If you perform a local-only resolution (e.g., resolving "localhost" or 127.0.0.1), it will still use the configured DNS service or /etc/hosts file but only return
 * local addresses if that is the only result for the query. However, in general usage, the endpoints returned represent external, remote destinations for network communication.
 *
 */

#include <boost/asio.hpp>
#include <iostream>

namespace asio = boost::asio;
using namespace std;

string make_daytime_string() {
    time_t now = time(0);
    return ctime(&now);
}

int main() {
    try {
        asio::io_context io;

        // create an acceptor endpoint.
        // endpoint is a combination of an IP address and a port number.
        // The IP Address will be the ANY address (INADDR_ANY or in6addr_any).
        asio::ip::tcp::acceptor acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 3313));

        // accept a connection
        while(true) {
            // create a tcp socket. this will be the connected socket when a TCP handshake completes.
            asio::ip::tcp::socket socket(io);
            acceptor.accept(socket);
            string datetime = make_daytime_string();
            boost::system::error_code ec;
            asio::write(socket, asio::buffer(datetime), ec);
        }
    } catch(const boost::system::error_code& e) {
        cerr << "Error: " << e.message() << endl;
    } catch(const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/* To test, just run "telnet localhost 3313" */