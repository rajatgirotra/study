/* A ChatClient will connect to ChatServer running on a host/port combination.
 * The ChatClient will read a message from the ChatServer and output on the terminal.
 * A ChatClient may be sending a message to other connected users and at the same time reading a new msg from the terminal.
 */

#include "chat_message.hpp"
#include <boost/asio.hpp>
#include <deque>
#include <array>
#include <iostream>
#include <thread>
#include <memory>
#include <ostream>
#include <string_view>
using namespace std;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

using ChatMessagePtr = std::shared_ptr<ChatMessage>;

class ChatClient : std::enable_shared_from_this<ChatClient> {
public:
    ChatClient(asio::io_context& io, const tcp::resolver::results_type& endpoints) : m_io(io), m_endpoints(endpoints),
                                                                                     m_socket(m_io) {

    }

    ~ChatClient() {
        close();
    }

    void close() noexcept {
        do_close();
    }

    void do_close() noexcept {
        if(m_socket.is_open()) {
            m_socket.close();
        }
    }

    void run() noexcept {
        // Connect can be synchronous as we only do it once.
        boost::system::error_code ec{};
        auto ep = asio::connect(m_socket, m_endpoints, ec);
        if(ec) {
            cout << "connect failed: " << ec.message() << endl;
            exit(1);
        }
        this->handle_connect(ep);
    }

    void handle_connect(tcp::endpoint ep) noexcept {
        cout << "Connected to remote endpoint: " << ep.address().to_string() << ", " << ep.port() << endl;
        this->handle_read_header();
    }

    void handle_read_header() noexcept {
        asio::async_read(m_socket, asio::buffer(m_msg_recv.data(), ChatMessage::HEADER_LENGTH), [self = shared_from_this()] (const boost::system::error_code& ec, size_t bytes) {
            if(ec) {
                cout << "read header failed: " << ec.message() << endl;
                exit(1);
            } else if(!self->m_msg_recv.decoder_header()) {
                cout << "decode header failed.\n";
                return;
            }
            self->handle_read_body();
        });
    }

    void handle_read_body() noexcept {
        asio::async_read(m_socket, asio::buffer(m_msg_recv.data(), m_msg_recv.bodyLength()), [self = shared_from_this()] (const boost::system::error_code& ec, size_t bytes) {
            if(ec) {
                cout << "read body failed: " << ec.message() << endl;
                exit(1);
            }
            cout << "Received: ";
            std::cout.write(self->m_msg_recv.data(), self->m_msg_recv.bodyLength());
            self->handle_read_header();
        });
    }

    void write(const string& msg) noexcept  {
        if(msg.size() > ChatMessage::MAX_MSG_SIZE) {
            cout << "failed to send msg: msg too long!\n";
            exit(1);
        }
        auto msgPtr = std::make_shared<ChatMessage>();
        msgPtr->bodyLength(msg.size());
        ::memcpy(msgPtr->data(), msg.data(), msg.size());
        if(!msgPtr->encode_header()) {
            cout << "failed to send msg: msg encoding failed\n";
            exit(1);
        }
        this->do_write(msgPtr);
    }

    void do_write(ChatMessagePtr msgPtr) noexcept {
        auto write_in_progress = !m_msgs.empty();
        m_msgs.emplace_back(msgPtr);
        this->handle_write(write_in_progress);
    }

    void handle_write(bool inProgress) noexcept {
        if(!inProgress) {
            asio::async_write(m_socket, asio::buffer(m_msgs.front()->data(), m_msgs.front()->bodyLength() + ChatMessage::HEADER_LENGTH),
                              [self = shared_from_this()] (const boost::system::error_code& ec, size_t bytes) {
                if(ec) {
                    cout << "failed to send msg to ChatServer: " << ec.message() << endl;
                    exit(1);
                }
                self->m_msgs.pop_front();
                if(!self->m_msgs.empty()) {
                    self->handle_write(false);
                }
            });
        }
    }
private:
    asio::io_context& m_io;
    const tcp::resolver::results_type m_endpoints;
    tcp::socket m_socket;
    ChatMessage m_msg_recv;
    std::deque<ChatMessagePtr> m_msgs;
};

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage:\n\t" << argv[0] << " <HOST> <PORT>\n";
        exit(1);
    }

    asio::io_context io;
    tcp::resolver resolver(io);
    auto endpoints = resolver.resolve(tcp::v4(), argv[1], argv[2]);
    auto client = std::make_shared<ChatClient>(io, endpoints);
    client->run();

    std::thread t([&] () { io.run(); });

    // start an endless loop to read message from terminal and forward to ChatClient.
    while(true) {
        string msg;
        std::getline(cin, msg);
        io.post([msg, client] () {client->write(msg);});
    }

    t.join();
}