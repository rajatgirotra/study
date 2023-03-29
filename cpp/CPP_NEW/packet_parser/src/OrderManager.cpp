#include "OrderManager.hpp"

void OrderManager::addOrder(const InAddOrder& order) {
    auto [it, result] = m_orders.emplace(order.m_orderRefNo, order);
    if(!result) {
        throw std::runtime_error("failed to insert duplicate order\n");
    }
}
void OrderManager::eraseOrder(std::uint64_t oid) {
    m_orders.erase(oid);
}

void OrderManager::eraseOrder(const InAddOrder& order) {
    eraseOrder(order.m_orderRefNo);
}

void OrderManager::updateOrder(const InAddOrder& order) {
    m_orders.erase(order.m_orderRefNo);
    m_orders.emplace(order.m_orderRefNo, order);
}

InAddOrder& OrderManager::getOrder(std::uint64_t oid)  {
    auto it = m_orders.find(oid);
    if(it != m_orders.end())
        return it->second;
    else
        throw std::runtime_error("failed to lookup order in order cache");
}

bool OrderManager::exists(std::uint64_t oid) const noexcept {
    return m_orders.find(oid) != m_orders.end();
}
