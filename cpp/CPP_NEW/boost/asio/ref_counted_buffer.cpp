/* A simple ref counted asio buffer */
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ctime>
using namespace std;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

string getTimeNow() {
    time_t t = std::time(0);
    char* x = std::ctime(&t);
    return string(x);
}

// this is a ref counted const buffer, so can only be used for write/async_write
class RefCountedBuffer {
private:
    std::shared_ptr<std::vector<char>> m_data;
    asio::const_buffer m_buffer;

public:
    RefCountedBuffer(const std::string& msg) : m_data(new std::vector<char>(msg.cbegin(), msg.cend())),
    m_buffer(m_data->data(), m_data->size()) {}

    ~RefCountedBuffer() {
        m_data.reset();
        cout << "Destroyed RefCountedBuffer\n";
    }

    // To use RefCountedBuffer as a ConstBufferSequence, we need to implement the requirements for ConstBufferSequence.
    // 1. declare a value_type
    using value_type = asio::const_buffer;

    //2. declare a const_iterator
    using const_iterator = const asio::const_buffer*;

    //3. have begin and end functions that return the const_iterator
    const_iterator begin() const noexcept { return &m_buffer; }
    const_iterator end() const noexcept { return &m_buffer + 1; }
};

class TCPConnection : public enable_shared_from_this <TCPConnection> {
    tcp::socket m_socket;
//    RefCountedBuffer m_buffer;
    std::array<char, 2048> m_data;

public:
    explicit TCPConnection(asio::io_context &io) : m_socket(io) {}

    tcp::socket& socket() noexcept {
        return m_socket;
    }

    void start() {
        handle_write();
    }

    void handle_write() {
        asio::async_write(
                m_socket,
                RefCountedBuffer(getTimeNow()),
                [self = shared_from_this()] (
                        const boost::system::error_code& ec,
                        size_t bytes_transferred) {
                });
    }
};


class TCPServer : public std::enable_shared_from_this<TCPServer> {
    asio::io_context& m_io;
    tcp::acceptor m_acceptor;

public:
    TCPServer(asio::io_context& io) : m_io(io), m_acceptor(m_io, tcp::endpoint (tcp::v4(), 7777)) {
        start_accept();
    }

    void start_accept() {
        auto conn = std::make_shared<TCPConnection>(m_io);
        m_acceptor.async_accept(conn->socket(), [this, conn] (const boost::system::error_code& ec) {
            if(!ec) {
                conn->start();
            }
            start_accept();
        });
    }
};

int main() {
    asio::io_context io;
    TCPServer server(io);
    io.run();
}