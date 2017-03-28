#ifndef _ORDER_MANAGER_HPP_INCLUDED_
#define _ORDER_MANAGER_HPP_INCLUDED_

#include "IExchange.hpp"
#include <memory>
#include <unordered_set>
#include <mutex>
#include "Order.hpp"

using exchange::IExchange;

namespace order_manager
{
    class OrderProcessor; //forward declaration.

    class OrderManager
    {
        private:
            //Reference to the exchange object which will notify us of
            //inserts, amends and cancellations.
            IExchange& m_exchange;

            //Insert, Amend and Cancellation callbacks. These will be registered
            //with the IExchange object.
            void onOrderInsert(int orderId, ErrorCode result);
            void onOrderAmend(int orderId, ErrorCode result);
            void onOrderCancel(int orderId, ErrorCode result);

            //C'tor & D'tor
            OrderManager(IExchange& roExchange);
            ~OrderManager();

            //disable copy c'tor and assignment
            OrderManager(const OrderManager&) = delete;
            OrderManager& operator = (const OrderManager&) = delete;

            //Custom deleter to unregister callbacks before deleting this OrderManager
            struct deleter
            { void operator()(OrderManager* poOrderManager); };

            //The order manager has an order processor to manage the life time of an order.
            std::unique_ptr<OrderProcessor> m_orderProcessor;

            //List of pending order ids
            std::unordered_set<int> m_pendingOrderSet;
            //We need a mutex for mutual exclusion since our callbacks are asynchronous.
            std::mutex m_mutex;

        public:
            //Helper function to create the OrderManager.
            static std::shared_ptr<OrderManager> create(IExchange&);

            //public interface for OrderManager
            void insertOrder(const std::string&, double, double, Side);
            void amendOrder(int, double);
            void cancelOrder(int);
            Order::State getOrderState(int);
    };
}//end of namespace order_manager

#endif // _ORDER_MANAGER_HPP_INCLUDED_
