#include "OrderStateMachine.hpp"
#include "Order.hpp"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;


using namespace order_manager;

OrderStateMachine_::OrderStateMachine_(const Order* poOrder) : m_parent(poOrder)
{
}

OrderStateMachine_::~OrderStateMachine_()
{}

void OrderStateMachine_::onAmend(const order_amended&)
{
    m_parent->m_state = Order::State::AMENDED;
    cout << "Changed order id " << m_parent->m_orderId << " state to AMENDED\n";
}

void OrderStateMachine_::onCancel(const order_cancelled&)
{
    m_parent->m_state = Order::State::CANCELLED;
    cout << "Changed order id " << m_parent->m_orderId << " state to CANCELLED\n";
}

