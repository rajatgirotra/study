#include "OrderManager.hpp"
#include <functional>
#include <iostream>
#include "OrderProcessor.hpp"

using namespace order_manager;
using std::cout;
using std::cerr;
using std::endl;

//C'tor for order manager
OrderManager::OrderManager(IExchange& roExchange) : m_exchange(roExchange),
                                                    m_orderProcessor(new OrderProcessor(*this))
{
    //Register callbacks here.
    m_exchange.onOrderInserted = std::bind(&OrderManager::onOrderInsert,
                                             this, std::placeholders::_1, std::placeholders::_2);
    m_exchange.onOrderAmended = std::bind(&OrderManager::onOrderAmend,
                                          this, std::placeholders::_1, std::placeholders::_2);
    m_exchange.onOrderCancelled = std::bind(&OrderManager::onOrderCancel,
                                            this, std::placeholders::_1, std::placeholders::_2);
}

//D'tor
OrderManager::~OrderManager()
{
    //reset callbacks.
    m_exchange.onOrderInserted  = nullptr;
    m_exchange.onOrderAmended = nullptr;
    m_exchange.onOrderCancelled = nullptr;
}

void OrderManager::deleter::operator() (OrderManager* poOrderManager)
{
    delete poOrderManager;
}

std::shared_ptr<OrderManager> OrderManager::create(IExchange& roExchange)
{
    std::shared_ptr<OrderManager> omPtr((new OrderManager(roExchange)), OrderManager::deleter());
    return omPtr;
}

//Insertion callback.
void OrderManager::onOrderInsert(int orderId, ErrorCode result)
{
    cout << "onOrderInsert called for orderId: " << orderId
         << ", ErrorCode: " << static_cast<std::underlying_type<ErrorCode>::type>(result) << "\n";
    if(ErrorCode::OK != result)
    {
        cerr << "IExchange did not accept order with orderId: " << orderId << endl;
        //Remove orderId from pending order list, as the order is not accepted by IExchange.
        {
            std::lock_guard<std::mutex> lck(m_mutex);
            m_pendingOrderSet.erase(orderId);
        }
        return;
    }
    //try to see if we have the order in our pending order list.
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        if(m_pendingOrderSet.find(orderId) == m_pendingOrderSet.end())
        {
            cerr << "Could not find order id: " << orderId << " in OrderManager" << endl;
            return;
        }
        //We found the pending order. Delete it and maintain an ACTIVE state for it.
        m_pendingOrderSet.erase(orderId);
    }
    //Hand-over things to OrderProcessor.
    m_orderProcessor->insert(orderId);
}

void OrderManager::onOrderAmend(int orderId, ErrorCode result)
{
    cout << "onOrderAmend called for orderId: " << orderId
         << ", ErrorCode: " << static_cast<std::underlying_type<ErrorCode>::type>(result) << "\n";
    if(ErrorCode::OK != result)
    {
        cerr << "IExchange did not amend order with orderId: " << orderId << endl;
        return;
    }
    m_orderProcessor->amend(orderId);
}

void OrderManager::onOrderCancel(int orderId, ErrorCode result)
{
    cout << "onOrderCancel called for orderId: " << orderId
         << ", ErrorCode: " << static_cast<std::underlying_type<ErrorCode>::type>(result) << "\n";
    if(ErrorCode::OK != result)
    {
        cerr << "IExchange did not cancel order with orderId: " << orderId << endl;
        return;
    }
    m_orderProcessor->cancel(orderId);
}

void OrderManager::insertOrder(const std::string& securityId, double price, double volume,
                               Side side)
{
    //Store the pending order id returned by IExchange
    {
        std::lock_guard<std::mutex> lck(m_mutex); 
        m_pendingOrderSet.insert(m_exchange.insertOrder(securityId, price, volume, side));
    }
    return;
}

void OrderManager::amendOrder(int orderId, double newVolume)
{
    //send amend order request to exchange. Wait for acknowledgement before you change the state
    //on your end.
    m_exchange.amendOrder(orderId, newVolume);
}

void OrderManager::cancelOrder(int orderId)
{
    //send cancel order request to exchange. Wait for ACK before you change the state on your end.
    m_exchange.cancelOrder(orderId);
}

Order::State OrderManager::getOrderState(int orderId)
{
    {
        std::lock_guard<std::mutex> lck(m_mutex);
        if(m_pendingOrderSet.find(orderId) != m_pendingOrderSet.end())
        {
            cout << "Orderid " << orderId << ", State PENDING\n";
            return Order::State::PENDING;
        }
    }
    //If we reach here, the order is not a pending order. Let OrderProcessor handle it.
    return m_orderProcessor->getOrderState(orderId);
}

