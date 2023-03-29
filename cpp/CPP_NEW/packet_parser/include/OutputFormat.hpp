#pragma once

#include <cstdint>
#include <ostream>

struct OutAddOrder {
    std::uint16_t m_msgType {0x01};
    std::uint16_t m_msgSize {44};
    char m_ticker[8] {};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo {};
    char m_side;
    char m_padding[3] {};
    std::uint32_t m_size{};
    double m_price{};

    friend std::ostream& operator << (std::ostream& os, const OutAddOrder&);
} __attribute__((packed));

struct OutOrderExecuted {
    std::uint16_t m_msgType {0x02};
    std::uint16_t m_msgSize {40};
    char m_ticker[8] {};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo {};
    std::uint32_t m_size{};
    double m_price{};

    friend std::ostream& operator << (std::ostream& os, const OutOrderExecuted&);
} __attribute__((packed));

struct OutOrderReduced {
    std::uint16_t m_msgType {0x03};
    std::uint16_t m_msgSize {32};
    char m_ticker[8] {};
    std::uint64_t m_timestamp {};
    std::uint64_t m_orderRefNo {};
    std::uint32_t m_sizeRemaining{};

    friend std::ostream& operator << (std::ostream& os, const OutOrderReduced&);
} __attribute__((packed));

struct OutOrderReplaced {
    std::uint16_t m_msgType {0x04};
    std::uint16_t m_msgSize {48};
    char m_ticker[8] {};
    std::uint64_t m_timestamp {};
    std::uint64_t m_originalOrderRefNo {};
    std::uint64_t m_newOrderRefNo {};
    std::uint32_t m_newSize{};
    double m_newPrice{};

    friend std::ostream& operator << (std::ostream& os, const OutOrderReplaced&);
} __attribute__((packed));