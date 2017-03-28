#ifndef _ORDER_PROCESSOR_HPP_INCLUDED_
#define _ORDER_PROCESSOR_HPP_INCLUDED_

#include <memory>
#include <mutex>
#include <unordered_map>
#include "Order.hpp"

namespace order_manager
{
    class OrderManager; //fwd declaration.

    class OrderProcessor
    {
        public:
            //ctor and dtor
            OrderProcessor(const OrderManager& roParent) : m_parent(roParent) {}
            ~OrderProcessor() {}

            //public interface, these are called by OrderManager when
            //we receive an asynchronous reply from IExchange.
            void insert(int orderId);
            void amend(int orderId);
            void cancel(int orderId);
            Order::State getOrderState(int orderId);
        private:
            //Reference to the OrderManager (parent of this class)
            const OrderManager& m_parent;

            //data structure to store Order details.
            typedef std::unordered_map<int /*orderId*/, std::shared_ptr<Order>> OrderMap;
            OrderMap m_orderMap;

            //mutex for mutual exclusion on OrderMap
            //Ideally a shared_mutex (Read-Write mutex should have been fine,
            //but C++11 doesn't have one).
            std::mutex m_mutex;
    };
}//end of namespace order_manager

#endif // _ORDER_PROCESSOR_HPP_INCLUDED_
