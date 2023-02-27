// A simple asynchronous TCP echo server.
// to test it, you can download from Boost Asio C++03 examples, a sample blocking_tcp_echo_client client app.

#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <ctime>
#include <string>
#include <array>

using namespace std;
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

string getTimeNow() {
    time_t t = std::time(0);
    char* x = std::ctime(&t);
    return string(x);
}

class handle_memory {
    // storage space
    char m_storage[1024];
    bool m_in_use {false};

public:
    explicit handle_memory() {}

    void* allocate(std::size_t sz) {
        if(m_in_use || sz > sizeof(m_storage)) {
            return ::operator new(sz);
        } else {
            m_in_use = true;
            return std::addressof(m_storage);
        }
    }

    void deallocate(void* address) {
        if(m_in_use) {
            m_in_use = false;
        } else {
            ::operator delete (address);
        }
    }
};

// the allocator to be associated with CompletionHandlers
template <typename T>
struct handle_allocator {
//private:
    handle_memory& m_memory;

public:
    using value_type = T;
    explicit handle_allocator(handle_memory& mem) : m_memory(mem) {}

    template <typename U>
    handle_allocator(const handle_allocator<U>& rhs) : m_memory(rhs.m_memory) {}

    bool operator == (const handle_allocator& rhs) const noexcept {
        return std::addressof(m_memory) == std::addressof(rhs.m_memory);
    }

    bool operator != (const handle_allocator& rhs) const noexcept {
        return !this->operator == (rhs);
    }

    T* allocate(std::size_t sz) {
        return static_cast<T*>(m_memory.allocate(sz));
    }

    void deallocate(T* address, size_t) {
        m_memory.deallocate(static_cast<void*>(address));
    }

    template <typename U>
    struct rebind {
        using other = handle_allocator<U>;
    };
};

class TCPConnection : public enable_shared_from_this <TCPConnection> {
    tcp::socket m_socket;
    std::array<char, 2048> m_data;
    handle_memory m_memory;

public:
    explicit TCPConnection(asio::io_context &io) : m_socket(io) {}

    tcp::socket& socket() noexcept {
        return m_socket;
    }

    void start() {
        handle_read();
    }

    void handle_read() {
        m_socket.async_read_some(
                asio::buffer(m_data),
                asio::bind_allocator(handle_allocator<int>(m_memory),
                [self = shared_from_this()] (
                        const boost::system::error_code& ec,
                        size_t bytes_transferred) {
                    if(!ec) {
                    self->handle_write(bytes_transferred);
                    }
                }));
    }

    void handle_write(size_t bytes) {
        asio::async_write(m_socket,
                asio::buffer(m_data.data(), bytes),
                asio::bind_allocator(handle_allocator<int>(m_memory),
                [self = shared_from_this()] (
                        const boost::system::error_code& ec,
                        size_t bytes_transferred) {
                    if(!ec) {
                        self->handle_read();
                    }
                }));
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
    std::thread t([&io] () {
//        io.run();
    });

    t.join();
}