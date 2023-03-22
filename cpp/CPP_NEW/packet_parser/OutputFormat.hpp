#pragma once

#include <cstdint>

struct OutAddOrder {
    std::uint16_t m_msgType {0x01};
    std::uint16_t m_msgSize {0x44};
    char m_ticker[8] {};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo {};
    char m_side;
    char m_padding[3] {};
    std::uint32_t m_size{};
    double m_price{};
} __attribute__((packed));

struct OutOrderExecuted {
    std::uint16_t m_msgType {0x02};
    std::uint16_t m_msgSize {0x40};
    char m_ticker[8] {};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo {};
    std::uint32_t m_size{};
    double m_price{};
} __attribute__((packed));

struct OutOrderReduced {
    std::uint16_t m_msgType {0x03};
    std::uint16_t m_msgSize {0x32};
    char m_ticker[8] {};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo {};
    std::uint32_t m_sizeRemaining{};
} __attribute__((packed));

struct OutOrderReplaced {
    std::uint16_t m_msgType {0x04};
    std::uint16_t m_msgSize {0x48};
    char m_ticker[8] {};
    std::uint64_t m_timestamp {};
    std::uint64_t m_originalOrderRefNo {};
    std::uint64_t m_newOrderRefNo {};
    std::uint32_t m_newSize{};
    double m_newPrice{};
} __attribute__((packed));