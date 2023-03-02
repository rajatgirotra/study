/* create multiple ChatServers at different ports. Each ChatServer object is essentially a ChatRoom.
 * A ChatRoom will have a list of participants that can join and be removed from the chat. A ChatRoom must maintain
 * the last 100 messages so that any new participant who joins can be sent all the old messages.
 */

#include "chat_message.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <deque>
#include <set>
#include <cstdlib>
#include <boost/asio.hpp>
#include <algorithm>
using namespace std;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

struct ChatParticipant {
    virtual ~ChatParticipant() = default;
    virtual void deliver(ChatMessage) = 0;
};

using ChatParticipantPtr = std::shared_ptr<ChatParticipant>;

class ChatRoom {
    static constexpr std::size_t MAX_MSGS = 100;
    std::deque<ChatMessage> m_msgs;
    std::set<ChatParticipantPtr> m_participants;

public:
    void join(ChatParticipantPtr participant) {
        // someone has newly joined. send saved messages of this chat to him
        m_participants.insert(participant);
        std::for_each(m_msgs.begin(), m_msgs.end(), [participant] (const ChatMessage& msg ) {
            participant->deliver(msg);
        });
    }

    void leave(ChatParticipantPtr participant) {
        m_participants.erase(participant);
    }

    void deliver(const ChatMessage& msg) {
        // make sure we retain only the last 100 messages.
        m_msgs.emplace_back(msg);
        while(m_msgs.size() > MAX_MSGS) {
            m_msgs.pop_front();
        }
        std::for_each(m_participants.begin(), m_participants.end(), [&msg] (const ChatParticipantPtr& participant ) {
            participant->deliver(msg);
        });
    }
};

class ChatSession : public enable_shared_from_this<ChatSession>, public ChatParticipant {
private:
    asio::io_context& m_io;
    tcp::socket m_socket;
    ChatRoom& m_room;
    ChatMessage m_msg;
    std::deque<ChatMessage> m_write_msgs;
public:
    ChatSession(asio::io_context& io, ChatRoom& room) : m_io(io), m_socket(m_io), m_room(room) {}

    tcp::socket& socket() noexcept { return m_socket; }

    void start() {
        // a participant has joined.
        m_room.join(shared_from_this());
        handle_read_header();
    }

    void handle_read_header() {
        asio::async_read(m_socket, asio::buffer(m_msg.data(), ChatMessage::HEADER_LENGTH),
                         [self = shared_from_this()] (const boost::system::error_code& ec, size_t bytes) {
            if(ec) {
                cout << "failed to read msg header: " << ec.message() << endl;
                // remove this participant
                self->m_room.leave(self->shared_from_this());
                return;
            }
            if(!self->m_msg.decoder_header()) {
                cout << "failed to decode chat msg: " << ec.message() << endl;
                // remove this participant
                self->m_room.leave(self->shared_from_this());
                return;
            }
            self->handle_read_body();
        });
    }

    void handle_read_body() {
        asio::async_read(m_socket,
                         asio::buffer(m_msg.data() + ChatMessage::HEADER_LENGTH,ChatMessage::MAX_MSG_SIZE),
                         [self = shared_from_this()] (const boost::system::error_code& ec, size_t bytes) {
            if(ec) {
                cout << "failed to read msg body: " << ec.message() << endl;
                // remove this participant
                self->m_room.leave(self->shared_from_this());
                return;
            }
            self->m_room.deliver(self->m_msg);
            self->handle_read_header(); // read next message.
        });
    }

    void deliver(const ChatMessage& msg) {
        bool need_to_write = m_write_msgs.empty();
        m_write_msgs.push_back(msg);
        handle_write(need_to_write);
    }

    void handle_write(bool need_to_write) {
        if(need_to_write) {
            asio::async_write(m_socket, asio::buffer(m_write_msgs.front().data(), ChatMessage::HEADER_LENGTH + m_write_msgs.front().bodyLength()),
                              [self = shared_from_this()] (const boost::system::error_code& ec, size_t bytes) {
                if(ec) {
                    cout << "failed writing chat msg: " << ec.message();
                    self->m_room.leave(self->shared_from_this());
                    return;
                }
                self->m_write_msgs.pop_front();
                self->handle_write(!self->m_write_msgs.empty());
            });
        }
    }
};

using ChatSessionPtr = std::shared_ptr<ChatSession>;

class ChatServer : public enable_shared_from_this<ChatServer> {
private:
    asio::io_context& m_io;
    int m_port;
    tcp::acceptor m_acceptor;
    ChatRoom m_room;
public:
    ChatServer(asio::io_context& io, int port) : m_io(io), m_port(port),
    m_acceptor(m_io, tcp::endpoint(tcp::v4(), m_port)) {
    }

    void accept() {
        auto session = std::make_shared<ChatSession>(m_io, m_room);
        m_acceptor.async_accept(session->socket(), [self = shared_from_this(), session] (const boost::system::error_code& ec) {
            if(ec) {
                cout << "failed to accept client connection: " << ec.message() << endl;
            } else {
                session->start();
            }
            self->accept(); // accept next connection
        });
    }
};

int main(int argc, char** argv) {
    if(argc < 2) {
        cout << "Usage:\n\t" << argv[0] << " <PORT> <PORT>...\n";
    }

    try {
        asio::io_context io;
        for(auto i = 1; i < argc; ++i) {
            std::make_shared<ChatServer>(io, atoi(argv[i]))->accept();
        }
        io.run();
    } catch(const std::exception& e) {
        cout << "exception caught in main: " << e.what() << endl;
    }
}