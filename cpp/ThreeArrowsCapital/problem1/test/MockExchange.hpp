#ifndef _MOCK_EXCHANGE_HPP_INCLUDED_
#define _MOCK_EXCHANGE_HPP_INCLUDED_

#include "../IExchange.hpp"
#include <set>
#include <thread>
#include <unordered_map>

namespace exchange
{
    class MockExchange : public IExchange
    {
        private:
            std::set<std::string> securities;
            std::set<int> orderList;

            //thread for asynchronous callbacks.
            std::thread* poThread;

            //orderId seed
            static const int m_orderIdSeed = 111110;
            int m_orderId;

            //Orders per security.
            typedef std::unordered_map<std::string, unsigned int> SecurityToOrderCountMap;
            SecurityToOrderCountMap m_secOrderCountMap;

            //Internal implementation for MockExchange.
            void doInsertOrder(int pendingOrderId, const std::string& securityId, double price, double volume, Side side);
            void doAmendOrder(int orderId, double newVolume);
            void doCancelOrder(int orderId);
        public:
            //c'tor & d'tor
            MockExchange();
            virtual ~MockExchange();
 
            //implement insertOrder, amendOrder and cancelOrder
            int insertOrder(const std::string& securityId, double price, double volume, Side side);
            void amendOrder(int orderId, double newVolume);
            void cancelOrder(int orderId);
    };
} //end of namespace exchange

#endif // _MOCK_EXCHANGE_HPP_INCLUDED_
