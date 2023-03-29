#pragma once

#include <unordered_map>
#include <cstdint>
#include "InputFormat.hpp"

class OrderManager {
    using OrdersMap = std::unordered_map<std::uint64_t, InAddOrder>;
    OrdersMap m_orders;
public:
    void addOrder(const InAddOrder&);
    void eraseOrder(const InAddOrder&);
    void eraseOrder(std::uint64_t oid);
    void updateOrder(const InAddOrder&);
    InAddOrder& getOrder(std::uint64_t oid);

    bool exists(std::uint64_t oid) const noexcept;
};