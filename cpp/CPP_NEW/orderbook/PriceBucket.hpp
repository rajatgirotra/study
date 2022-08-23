#pragma once

#include "Order.hpp"
#include <deque>
using std::deque;

namespace raj {
    class PriceBucket {
    private:
        std::deque<Order> m_orders;
        uint64_t m_pricepoint;
        uint64_t m_totalvolume;
        uint64_t m_totalcount;

    public:
        PriceBucket(uint64_t arg = 0) : m_pricepoint(arg), m_totalvolume(0), m_totalcount(0) {}

        uint64_t getTotalVolume() const noexcept { return m_totalvolume; }
        uint64_t getTotalCount() const noexcept { return m_totalcount; }

        void addOrder(const Order& o) {
            m_orders.emplace_back(o);
            ++m_totalcount;
            m_totalvolume += o.m_size;
        }

        bool removeOrder(uint64_t orderid) {
            auto it = std::find_if(m_orders.begin(), m_orders.end(), [&](const auto &item) {
                return item.m_orderid == orderid;
            });

            if(it != m_orders.end()) {
                --m_totalcount;
                m_totalvolume -= it->m_size;
                m_orders.erase(it);
                return true;
            }
            return false;
        }

        bool removeOrder(const Order& o) {
            return removeOrder(o.m_orderid);
        }

        auto begin() { return m_orders.begin(); }
        auto end() { return m_orders.end(); }

        uint64_t pricePoint() const noexcept { return m_pricepoint; }

    };

} // raj

