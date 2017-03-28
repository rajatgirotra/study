#include "MockExchange.hpp"
#include "../OrderManager.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <gtest/gtest.h>

using exchange::MockExchange;
using namespace order_manager;
using std::cout;
using std::cin;
using std::endl;

struct OrderManagerTest : public ::testing::Test
{
    MockExchange m_mockExchange;
    std::shared_ptr<OrderManager> m_orderManagerPtr;

    OrderManagerTest() : m_orderManagerPtr(OrderManager::create(m_mockExchange))
    {};

    ~OrderManagerTest() {}
};


TEST_F(OrderManagerTest, InsertCleanOrder)
{
    m_orderManagerPtr->insertOrder("IBM", 23.5, 100, Side::BUY);//Buy 100 shared of IBM at 23.5
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait a second for IExchange to confirm order.
    //Assert order state should be ACTIVE.
    ASSERT_EQ(Order::State::ACTIVE, m_orderManagerPtr->getOrderState(111111));
}

TEST_F(OrderManagerTest, InsertZeroPriceOrder)
{
    m_orderManagerPtr->insertOrder("IBM", 0, 100, Side::BUY);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait a second for IExchange to confirm order.
    //Assert order state should be UNAVAILABLE.
    ASSERT_EQ(Order::State::UNAVAILABLE, m_orderManagerPtr->getOrderState(111111));
}

TEST_F(OrderManagerTest, InsertZeroVolume)
{
    m_orderManagerPtr->insertOrder("IBM", 23.5, 0, Side::BUY);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait a second for IExchange to confirm order.
    //Assert order state should be UNAVAILABLE.
    ASSERT_EQ(Order::State::UNAVAILABLE, m_orderManagerPtr->getOrderState(111111));
}

TEST_F(OrderManagerTest, InsertInvalidSecurityOrder)
{
    m_orderManagerPtr->insertOrder("MICROSOFT", 23.5, 0, Side::BUY);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait a second for IExchange to confirm order.
    //Assert order state should be UNAVAILABLE.
    ASSERT_EQ(Order::State::UNAVAILABLE, m_orderManagerPtr->getOrderState(111111));
}

TEST_F(OrderManagerTest, InsertTooManyOrders)
{
    m_orderManagerPtr->insertOrder("APPLE", 23.5, 10, Side::BUY); //orderid 111111
    m_orderManagerPtr->insertOrder("APPLE", 23.5, 10, Side::BUY);
    m_orderManagerPtr->insertOrder("APPLE", 23.5, 10, Side::BUY);
    m_orderManagerPtr->insertOrder("APPLE", 23.5, 10, Side::BUY);
    m_orderManagerPtr->insertOrder("APPLE", 23.5, 10, Side::BUY);
    m_orderManagerPtr->insertOrder("APPLE", 23.5, 10, Side::BUY);//orderid 111116
    std::this_thread::sleep_for(std::chrono::seconds(2)); //Wait a second for IExchange to confirm order.
    ASSERT_EQ(Order::State::ACTIVE, m_orderManagerPtr->getOrderState(111111));
    ASSERT_EQ(Order::State::ACTIVE, m_orderManagerPtr->getOrderState(111112));
    ASSERT_EQ(Order::State::ACTIVE, m_orderManagerPtr->getOrderState(111113));
    ASSERT_EQ(Order::State::ACTIVE, m_orderManagerPtr->getOrderState(111114));
    ASSERT_EQ(Order::State::ACTIVE, m_orderManagerPtr->getOrderState(111115));
    ASSERT_EQ(Order::State::UNAVAILABLE, m_orderManagerPtr->getOrderState(111116));
}


TEST_F(OrderManagerTest, AmendCleanOrder)
{
    m_orderManagerPtr->insertOrder("DELL", 67.98, 1000, Side::SELL);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait a second for IExchange to confirm order.
    m_orderManagerPtr->amendOrder(111111, 2000);
    //Assert order state should be AMENDED.
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait a second for IExchange to confirm amend
    ASSERT_EQ(Order::State::AMENDED, m_orderManagerPtr->getOrderState(111111));
}

TEST_F(OrderManagerTest, CancelCleanOrder)
{
    m_orderManagerPtr->insertOrder("DELL", 67.98, 1000, Side::SELL);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait a second for IExchange to confirm order.
    m_orderManagerPtr->cancelOrder(111111);
    //Assert order state should be CANCELLED.
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait a second for IExchange to confirm cancel
    ASSERT_EQ(Order::State::CANCELLED, m_orderManagerPtr->getOrderState(111111));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

