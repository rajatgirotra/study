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

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class ChatClient {

};