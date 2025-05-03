module;

#include <iostream>
#include <format>

module MyModule;

double Customer::sumPrice() const {
    double sum = 0.0;
    for (const Order &od: m_orders) {
        sum += od.m_count * od.m_price;
    }
    return sum;
}

double Customer::averagePrice() const {
    if (m_orders.empty()) {
        return 0.0;
    }
    return sumPrice() / m_orders.size();
}

void Customer::print() const {
    // print name:
    std::cout << m_name << ":\n";
    // print order entries:
    for (const auto &od: m_orders) {
        std::cout << std::format("{:3} {:14} {:6.2f} {:6.2f}\n",
                                 od.m_count, od.m_item, od.m_price, od.m_count * od.m_price);
    }
    // print sum:
    std::cout << std::format("{:25} ------\n", ' ');
    std::cout << std::format("{:25} {:6.2f}\n", "    Sum:", sumPrice());
}
