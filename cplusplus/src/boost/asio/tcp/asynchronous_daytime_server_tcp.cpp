/*
 * Asynchronous Daytime Server
 */

#include <boost/asio.hpp>
#include <iostream>
#include <memory>

namespace asio = boost::asio;
using namespace std;

string make_daytime_string() {
    time_t now = time(0);
    return ctime(&now);
}

class Connection : public std::enable_shared_from_this<Connection> {
private:
    asio::io_context& m_io;
    asio::ip::tcp::socket m_socket;

    explicit Connection(asio::io_context& io) : m_io(io), m_socket(m_io) {
    }

public:
    using Ptr = std::shared_ptr<Connection>;

    asio::ip::tcp::socket& socket() noexcept { return m_socket; }

    static Ptr create(asio::io_context& io) {
        return Ptr(new Connection(io));
    }

    void start() {
        string datetime = make_daytime_string();
        asio::async_write(m_socket, asio::buffer(datetime), [self = shared_from_this()]
        (const boost::system::error_code& ec, [[maybe_unused]] size_t bytes_transferred) {
            if(ec) {
                cerr << "Error: " << ec.message() << endl;
            }
        });
    }
};

class AsyncDaytimeServer : public std::enable_shared_from_this<AsyncDaytimeServer> {
private:
    asio::io_context& m_io;
    asio::ip::tcp::acceptor m_acceptor;
public:
    explicit AsyncDaytimeServer(asio::io_context& io)  try : m_io(io), m_acceptor(m_io) {
        asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), 3313);
        // open, set_option, bind and listen sequence
        m_acceptor.open(ep.protocol());
        m_acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
        m_acceptor.bind(ep);
        m_acceptor.listen();
    } catch(const boost::system::error_code& e) {
        throw std::runtime_error(e.message());
    }

    void run() {
        start_accept();
    }

    void start_accept() {
        auto conn = Connection::create(m_io);
        m_acceptor.async_accept(conn->socket(), [self = shared_from_this(), conn = conn] (const boost::system::error_code ec) {
            if(!ec) {
                conn->start();
            } else {
                cerr << "Error: " << ec.message() << endl;
            }
            self->start_accept();
        });
        cout << "Accepting!" << endl;
    }
};

int main() {
    try {
        asio::io_context io;
        make_shared<AsyncDaytimeServer>(io)->run();
        io.run();
    } catch(const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/* To test, just run "telnet localhost 3313" */