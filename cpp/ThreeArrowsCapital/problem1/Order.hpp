#ifndef _ORDER_HPP_INCLUDED_
#define _ORDER_HPP_INCLUDED_

#include <mutex>
#include <memory>
#include <boost/operators.hpp>
#include <boost/msm/back/state_machine.hpp>

namespace order_manager
{
    class OrderStateMachine_; //fwd declaration
    typedef boost::msm::back::state_machine<OrderStateMachine_> OrderStateMachine;
    struct Order : private boost::equivalent<Order>
    {
        enum class State
        {
            UNAVAILABLE,
            PENDING,
            ACTIVE,
            AMENDED,
            CANCELLED,
            REJECTED
        };

        int m_orderId; //orderId
        mutable State m_state;//Only state can be changed by the state machine.
        std::unique_ptr<OrderStateMachine> m_stateMachine;
        std::mutex m_mutex;

        //ctor & dtor
        Order(const int& pId);
        ~Order();

        bool operator < (const Order& rhs) const;
    };
}//end of namespace order_manager


#endif // _ORDER_HPP_INCLUDED_
