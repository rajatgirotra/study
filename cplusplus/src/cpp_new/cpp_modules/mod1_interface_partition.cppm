module;

#include <string>
#include <vector>

export module MyModule:Customer;

// list of internal partitions
import :Order;

export class Customer {
    std::string m_name;
    std::vector<Order> m_orders;

public:
    Customer(const std::string& n) : m_name{n} {
    }
    void buy(const std::string& ordername, double price) {
        m_orders.push_back(Order{ordername, 1, price});
    }
    void buy(int num, const std::string& ordername, double price) {
        m_orders.push_back(Order{ordername, num, price});
    }

    double sumPrice() const;
    double averagePrice() const;
    void print() const;
};
