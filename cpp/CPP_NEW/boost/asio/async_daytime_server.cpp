#include <iostream>
#include <memory>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <atomic>
#include <ctime>
#include <string>
#include <thread>
using namespace std;
namespace asio = boost::asio;

string getTimeNow() {
    time_t t = time(0);
    char* x = ctime(&t);
    return string(x);
}

class TCPConnection {
    asio::io_context& m_io;
    asio::ip::tcp::socket m_socket;

    using TCPConnectionPtr = std::shared_ptr<TCPConnection>;

public:
    static std::atomic_int m_active_connections;
    explicit TCPConnection(asio::io_context& io) : m_io(io), m_socket(m_io) {}

    ~TCPConnection() {
        atomic_fetch_sub(&m_active_connections, 1);
        cout << "Active Connections: " << atomic_load(&m_active_connections) << endl;
    }

    static TCPConnectionPtr create(asio::io_context& io) {
        return std::make_shared<TCPConnection>(io);
    }

    asio::ip::tcp::socket& socket() noexcept { return m_socket; }

    void start() {
        atomic_fetch_add(&m_active_connections, 1);
        boost::asio::async_write(m_socket, asio::buffer(getTimeNow()), [this] (const boost::system::error_code& ec, size_t bytes_transferred) {
            // ignore err and bytes transferred
        });
    }
};

class TCPServer {
    asio::io_context& m_io;
    asio::ip::tcp::acceptor m_acceptor;
public:
    explicit TCPServer(asio::io_context& io) : m_io(io), m_acceptor(m_io, asio::ip::basic_endpoint(asio::ip::tcp::v4(), 7777)) {
        start();
    }

    void start() {
        auto conn = TCPConnection::create(m_io);

        m_acceptor.async_accept(conn->socket(), [this, conn](const boost::system::error_code& ec) {
            if(!ec)
                conn->start();
            this->start();
        });
    }
    // The conn shared_ptr gets destroyed when start() finishes, so counting the number of active connections is a challenge
};

std::atomic_int TCPConnection::m_active_connections{0};

int main() {
    asio::io_context io;
    TCPServer server(io);

    io.run();

    std::thread t([&io] () {
        io.run();
    });

    t.join();

}