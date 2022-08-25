#include "Orderbook.hpp"
#include <iostream>
#include <random>

using namespace std;
using namespace raj;

Order randomOrder() {
    static uint32_t orderid {};
    Order o;
    ++orderid;
    o.m_orderid = orderid;

    static std::random_device r;
    static std::default_random_engine engine(r());
    static std::uniform_int_distribution<uint32_t> rand_price(1000000, 2000000);
    static std::uniform_int_distribution<uint32_t> rand_size(1, 50);
    o.m_price = rand_price(engine);
    o.m_size = rand_size(engine);

    o.m_clientid = 1;

    o.m_side = (rand_size(engine) % 2 == 0 ? Side::BUY : Side::SELL);

    return o;
}

int main(int argc, char** argv) {
    Book<Side::BUY> buyBook;
    for(int i = 0; i < 10; ++i) {
        buyBook.addOrder(randomOrder());
    }

    auto start_it = buyBook.begin();
    auto end_it = buyBook.end();

    while(start_it != end_it) {
        cout << *start_it << endl;
        ++start_it;
    }

}