#include "MockExchange.hpp"
#include <iostream>
#include <future>
#include <thread>
using std::cout;
using std::endl;

using namespace exchange;

const int MockExchange::m_orderIdSeed;

MockExchange::MockExchange() : poThread(nullptr), m_orderId(m_orderIdSeed)
{
    securities.insert("IBM");
    securities.insert("DELL");
    securities.insert("APPLE");

    m_secOrderCountMap["IBM"] = 5;
    m_secOrderCountMap["DELL"] = 5;
    m_secOrderCountMap["APPLE"] = 5;

}

MockExchange::~MockExchange()
{
    delete poThread;
}

int MockExchange::insertOrder(const std::string& securityId, double price,
                              double volume, Side side)
{
    ++m_orderId;
    poThread = new std::thread(&MockExchange::doInsertOrder, this, m_orderId, securityId, price, volume, side);
    poThread->detach();
//    std::async(std::launch::async, &MockExchange::doInsertOrder, this, orderId, securityId, price, volume, side);
    return m_orderId;
}

void MockExchange::amendOrder(int orderId, double newVolume)
{
    poThread = new std::thread(&MockExchange::doAmendOrder, this, orderId, newVolume);
    poThread->detach();
    //std::async(std::launch::async, &MockExchange::doAmendOrder, this, orderId, newVolume);
    return;
}

void MockExchange::cancelOrder(int orderId)
{
    poThread = new std::thread(&MockExchange::doCancelOrder, this, orderId);
    poThread->detach();
    //std::async(std::launch::async, &MockExchange::doCancelOrder, this, orderId);
    return;
}


void MockExchange::doInsertOrder(int pendingOrderId, const std::string& securityId, double price, double volume,
                                 Side side)
{
    ErrorCode result = ErrorCode::OK;
    //Validate order
    if(securities.find(securityId) == securities.end())
    { 
        //Security Not found, return error
        result = ErrorCode::UNKNOWN_SECURITY;
    }
    else if( (price <= 0) || (volume <= 0) || ((side != Side::BUY) && (side != Side::SELL)))
    {
        //INVALID ARGUMENTS
        result = ErrorCode::INVALID_ARGUMENTS;
    }
    else if(m_secOrderCountMap[securityId] <= 0)
    {
        //TOO MANY ORDERS
        result = ErrorCode::TOO_MANY_ORDERS;
    }else {
        m_secOrderCountMap[securityId]--;
        orderList.insert(pendingOrderId);
    }

    if(onOrderInserted)
    {
        onOrderInserted(pendingOrderId, result);
    }
//    cout << "MockExchange: New order created, orderId: " << pendingOrderId << endl;
}

void MockExchange::doAmendOrder(int orderId, double newVolume)
{
    ErrorCode result = ErrorCode::OK;
    std::set<int>::iterator it;
    if(newVolume <= 0)
    {
        //Invalid newVolume
        result = ErrorCode::INVALID_ARGUMENTS;
    }
    else
    {
        it = orderList.find(orderId);
        if(it == orderList.end())
            result = ErrorCode::UNKNOWN_ORDER;
    }

    if(onOrderAmended)
    {
        onOrderAmended(orderId, result);
        //cout << "MockExchange:  Order amended, orderId: " << orderId << endl;
    }
}

void MockExchange::doCancelOrder(int orderId)
{
    ErrorCode result = ErrorCode::OK;
    std::set<int>::iterator it;
    it = orderList.find(orderId);
    if(it == orderList.end())
    {
        result = ErrorCode::UNKNOWN_ORDER;
    }

    if(onOrderCancelled)
    {
        onOrderCancelled(orderId, result);
        //cout << "MockExchange:  Order cancelled, orderId: " << orderId << endl;
    }
}
