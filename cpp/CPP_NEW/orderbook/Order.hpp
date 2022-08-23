#pragma once

#include <cstdint>

namespace raj {
    enum struct Side {
        BUY,
        SELL
    };

    struct Order {
        uint64_t m_orderid;
        uint64_t m_price; // fixed point 6.4 representation.
        uint32_t m_size;
        uint64_t m_clientid;
        Side m_side;
    };
}