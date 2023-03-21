#include "InputFormat.hpp"

std::ostream& operator << (std::ostream& os, const InAddOrder& rhs) {
    os << rhs.m_msgType << " " << rhs.m_timestamp << " " << rhs.m_orderRefNo
    << " " << (rhs.m_side == Side::Sell ? "Sell" : "Buy") << " " << rhs.m_ticker
    << " " << rhs.m_size << " " << rhs.m_price;
    return os;
}

std::ostream& operator << (std::ostream& os, const InOrderExecuted& rhs) {
    os << rhs.m_msgType << " " << rhs.m_timestamp << " " << rhs.m_orderRefNo
       << " " << rhs.m_size;
    return os;
}

std::ostream& operator << (std::ostream& os, const InOrderCancelled& rhs) {
    os << rhs.m_msgType << " " << rhs.m_timestamp << " " << rhs.m_orderRefNo
       << " " << rhs.m_size;
    return os;
}

std::ostream& operator << (std::ostream& os, const InOrderReplaced& rhs) {
    os << rhs.m_msgType << " " << rhs.m_timestamp << " " << rhs.m_originalOrderRefNo
       << " " << rhs.m_newOrderRefNo << " " << rhs.m_size << " " << rhs.m_price;
    return os;
}