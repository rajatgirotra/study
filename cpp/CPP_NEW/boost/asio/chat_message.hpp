/*
 * Create a chat application where we create two binaries
 * chat_client: This will connect to a chat_server running on a port. Multiple chat_clients connecting to the same chat_server at the same port can exchange messages over TCP.
 * chat_server: A server that can accept incoming TCP connections on multiple ports provided as argument. Each port can have multiple chat_clients
 * connected to it. All chat_clients connected to the ChatServer at the same port exchange messages with each other.
 *
 * messages are plain ascii and assume that maximum size of a single message is 512 characters.
 */
#pragma once

#include <array>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <charconv>
struct ChatMessage {
    static constexpr std::size_t HEADER_LENGTH = 4;
    static constexpr std::size_t MAX_MSG_SIZE = 512;

    ChatMessage() = default;

    const char* body() const noexcept { return m_msg.data(); }
    char* body() noexcept { return m_msg.data(); }

    const char* data() const noexcept { return m_msg.data() + HEADER_LENGTH; }
    char* data() noexcept { return m_msg.data() + HEADER_LENGTH; }

    std::size_t bodyLength() const noexcept { return m_body_length; }
    void bodyLength(std::size_t newLength) noexcept {
        m_body_length = std::min(newLength, MAX_MSG_SIZE);
    }

    bool encode_header() noexcept {
        std::array<char, HEADER_LENGTH> header{};
        sprintf(header.data(), "%04d", static_cast<int>(m_body_length));
        memcpy(m_msg.data(), header.data(), HEADER_LENGTH);
        return true;
    }

    bool decoder_header() noexcept {
        auto [ptr, ec] = std::from_chars(m_msg.data(), m_msg.data() + HEADER_LENGTH, m_body_length, 10);
        if(ec == std::errc() && m_body_length < MAX_MSG_SIZE) {
            return true;
        } else {
            m_body_length = 0;
            return false;
        }
    }

private:
    std::size_t m_body_length {};
    std::array<char, HEADER_LENGTH + MAX_MSG_SIZE> m_msg {};
};