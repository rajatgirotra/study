#include <iostream>
#include <memory>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <atomic>
#include <ctime>
#include <string>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;
namespace asio = boost::asio;

string getTimeNow() {
    time_t t = time(0);
    char* x = ctime(&t);
    return string(x);
}

class TCPServer;

class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    asio::io_context& m_io;
    asio::ip::tcp::socket m_socket;
    TCPServer& m_tcpserver;

    using TCPConnectionPtr = std::shared_ptr<TCPConnection>;

public:
//    static std::atomic_int m_active_connections;
    explicit TCPConnection(asio::io_context& io, TCPServer& server) : m_io(io), m_socket(m_io), m_tcpserver(server) {}

    ~TCPConnection() {
//        atomic_fetch_sub(&m_active_connections, 1);
        cout << "In destructor\n";
//        cout << "Active Connections: " << atomic_load(&m_active_connections) << endl;
    }

    static TCPConnectionPtr create(asio::io_context& io, TCPServer& server) {
        return std::make_shared<TCPConnection>(io, server);
    }

    asio::ip::tcp::socket& socket() noexcept { return m_socket; }

    void terminate(TCPConnectionPtr conn);

    void start() {
          boost::asio::async_write(m_socket, asio::buffer(getTimeNow()), [this] (const boost::system::error_code& ec, size_t bytes_transferred) {
            // ignore err and bytes transferred.
            // the physical TCP connection is still live at this point. a FIN will be sent at the end of this CompletionHandler.
            cout << "in async write\n";
            cout << "socket: is_open, " << m_socket.is_open() << " " << m_socket.local_endpoint().address().to_string() << ", " << m_socket.local_endpoint().port() << endl;
//            std::this_thread::sleep_for(5s);
            terminate(shared_from_this());
        });
    }
};

class TCPServer {
    asio::io_context& m_io;
    asio::ip::tcp::acceptor m_acceptor;
    std::vector<std::shared_ptr<TCPConnection>> m_connections;
    static atomic_int m_active_connections;
public:
    explicit TCPServer(asio::io_context& io) : m_io(io), m_acceptor(m_io, asio::ip::basic_endpoint(asio::ip::tcp::v4(), 7777)) {
        start();
    }

    void terminate(std::shared_ptr<TCPConnection> conn) {
        auto iter = std::find_if(begin(m_connections), end(m_connections), [conn](const auto& ptr) {
            // connection id.
            return conn == ptr;
        });

        if (iter != m_connections.end()) {
            (*iter)->socket().close();
//            atomic_fetch_sub(&m_active_connections, 1);
            cout << "Active connections: " << atomic_load(&m_active_connections) << endl;
            m_connections.erase(iter);
        }
    }

    void start() {
        auto conn = TCPConnection::create(m_io, *this);
        m_connections.emplace_back(conn);
        cout << "A conn use_count: " << conn.use_count() << endl;

        m_acceptor.async_accept(conn->socket(), [this, conn](const boost::system::error_code& ec) {
            atomic_fetch_add(&m_active_connections, 1);
            cout << "Active connections: " << atomic_load(&m_active_connections) << endl;
            cout << "B conn use_count: " << conn.use_count() << endl;
            this->start();
            if(!ec)
                conn->start();
        });
    }
    // The conn shared_ptr gets destroyed when start() finishes, because it is part of the lambda closure class. and the closure object gets destroyed at the end
    // of this function. With that the socket object in the TCPConnection class also gets destroyed; so the server sends a TCP FIN to client and then the TCPConnection destructor
    // is called which decreases the number of activate connections. so accessing "this" in async_write() will be undefined behavior as the object is already destroyed.
    // so we create a vector to keep connection shared ptr, so connection object use_count stays > 0 after this function finishes.
};

std::atomic_int TCPServer::m_active_connections{0};

void TCPConnection::terminate(TCPConnectionPtr conn) {
    m_tcpserver.terminate(conn);
}

int main() {
    asio::io_context io;
    TCPServer server(io);

    io.run();

    std::thread t1([&io] () {
        io.run();
    });

    std::thread t2([&io] () {
//        io.run();
    });

    t1.join();
    t2.join();

}