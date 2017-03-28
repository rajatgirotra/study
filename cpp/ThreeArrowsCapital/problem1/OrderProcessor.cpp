#include "OrderProcessor.hpp"
#include <iostream>
#include "Order.hpp"
#include "OrderEvents.hpp"
#include "OrderStateMachine.hpp"

using std::cout;
using std::cerr;
using std::endl;

using namespace order_manager;

void OrderProcessor::insert(int orderId)
{
    //Create a new Order. Order has a state machine to manage itself.
    std::shared_ptr<Order> order(new Order(orderId));
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        OrderMap::iterator it;
        it = m_orderMap.find(orderId);
        if(it != m_orderMap.end())
        {
            cerr << "Order id " << orderId << " already exists. Cannot insert again\n";
            return;
        }
        m_orderMap.insert(std::make_pair(orderId, order));
    }
    cout << "OrderId " << orderId << " inserted. state is ACTIVE.\n";
    return;
}

void OrderProcessor::amend(int orderId)
{
    //Create a new event order_amended and send it to the state machine.
    OrderMap::iterator it;
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        it = m_orderMap.find(orderId);
        if(it == m_orderMap.end())
        {
            cerr << "Order id " << orderId << " does not exist. Cannot amend\n";
            return;
        }
    }

    //Lets amend it now.
    {
        std::shared_ptr<Order>& order = it->second;
        std::lock_guard<std::mutex> lck(order->m_mutex);
        order_amended event;//create event
        order->m_stateMachine->process_event(event); //give it to order's state machine
    }

    return; 
}

void OrderProcessor::cancel(int orderId)
{
    //Create a new event order_cancelled and send it to the state machine.
    OrderMap::iterator it;
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        it = m_orderMap.find(orderId);
        if(it == m_orderMap.end())
        {
            cerr << "Order id " << orderId << " does not exist. Cannot cancel\n";
            return;
        }
    }

    {
        std::shared_ptr<Order>& order = it->second;
        std::lock_guard<std::mutex> lck(order->m_mutex);
        order_cancelled event;
        order->m_stateMachine->process_event(event);
    }

    return;
}

Order::State OrderProcessor::getOrderState(int orderId)
{
    OrderMap::iterator it;
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        it = m_orderMap.find(orderId);
        if(it == m_orderMap.end())
        {
            cerr << "Order id " << orderId << " does not exist. Cannot view\n";
            return Order::State::UNAVAILABLE;
        }
    }

    std::shared_ptr<Order>& orderPtr = it->second;
    cout <<"Orderid " << orderId;
    switch(orderPtr->m_state)
    {
        case Order::State::ACTIVE : cout << ", State is ACTIVE\n"; return Order::State::ACTIVE;
        case Order::State::AMENDED : cout << ", State is AMENDED\n";  return Order::State::AMENDED; 
        case Order::State::CANCELLED : cout << ", State is CANCELLED\n"; return Order::State::CANCELLED;
        default : cout << ", State is UNAVAILABLE\n"; return Order::State::UNAVAILABLE;
    }
    return Order::State::UNAVAILABLE;
}

