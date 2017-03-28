#ifndef _IEXCHANGE_HPP_INCLUDED_
#define _IEXCHANGE_HPP_INCLUDED_

#include <functional>
#include <string>
#include "Enums.hpp"

namespace exchange
{
    class IExchange
    {
        public:
            //Callback function type on order insertion
            typedef std::function<void(int orderId, ErrorCode errorCode)> OrderInsertedCallback;

            //Callback function type on order amendment
            typedef std::function<void(int orderId, ErrorCode errorCode)> OrderAmendedCallback;

            //Callback function type on order cancellation
            typedef std::function<void(int orderId, ErrorCode errorCode)> OrderCancelledCallback;

            //D'tor
            virtual ~IExchange() {}

            //insert new order, returns pending order id.
            virtual int insertOrder(const std::string& securityId, double price, double volume, Side side) = 0;

            //Amend order volume
            virtual void amendOrder(int orderId, double newVolume) = 0;

            //Cancel order
            virtual void cancelOrder(int orderId) = 0;

            //Callbacks
            OrderInsertedCallback onOrderInserted;
            OrderAmendedCallback onOrderAmended;
            OrderCancelledCallback onOrderCancelled;
    };
}//end of namespace exchange

#endif // _IEXCHANGE_HPP_INCLUDED_
