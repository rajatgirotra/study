#pragma once

#include <array>
#include <cstdint>
#include <ostream>

struct Packet {
    std::uint16_t m_size {};
    std::uint32_t m_seqNo {};
    std::uint16_t m_payloadSize{};
    std::array<char, (1<<16)> m_payload {}; // 65536 bytes is enough space.

    bool operator > (const Packet& rhs) const noexcept {
        return this->m_seqNo > rhs.m_seqNo;
    }

    Packet() = default;
    // disable copy
    Packet(const Packet&) = delete;
    Packet& operator = (const Packet&) = delete;

    // enable move
    Packet(Packet&&) = default;
    Packet& operator = (Packet&&) = default;
};

enum struct Side : char {
    Buy,
    Sell
};

struct InAddOrder {
    char m_msgType {'A'};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo {};
    Side m_side{};
    std::uint32_t m_size{};
    char m_ticker[9]{};
    std::int32_t m_price{};

    friend std::ostream& operator << (std::ostream& os, const InAddOrder&);
};

struct InOrderExecuted {
    char m_msgType {'E'};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo{};
    std::uint32_t m_size;
    friend std::ostream& operator << (std::ostream& os, const InOrderExecuted&);
};

struct InOrderCancelled {
    char m_msgType {'X'};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo{};
    std::uint32_t m_size{};
    friend std::ostream& operator << (std::ostream& os, const InOrderCancelled&);
};

struct InOrderReplaced {
    char m_msgType {'R'};
    std::uint64_t m_timestamp {};
    std::uint64_t m_originalOrderRefNo{};
    std::uint64_t m_newOrderRefNo{};
    std::uint32_t m_size{};
    std::int32_t m_price{};
    friend std::ostream& operator << (std::ostream& os, const InOrderReplaced&);
};
