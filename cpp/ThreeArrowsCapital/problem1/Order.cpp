#include "Order.hpp"
#include "OrderStateMachine.hpp"

using namespace order_manager;

//ctor & dtor
Order::Order(const int& pID ) : m_orderId(pID)
                                ,m_state(State::ACTIVE)
                                ,m_stateMachine(new OrderStateMachine(this))
{
    m_stateMachine->start();
}

Order::~Order()
{
    m_stateMachine->stop();
}

//Comparison operator
bool Order::operator < (const Order& rhs) const
{ return (m_orderId < rhs.m_orderId); }
