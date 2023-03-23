//
// Created by rajatgirotra on 22/3/23.
//

#include "OutputFormat.hpp"

std::ostream& operator << (std::ostream& os, const OutAddOrder& order) {
    os << order.m_msgType << " " << order.m_msgSize << "  "
    << order.m_ticker << " " << order.m_timestamp << " "
    << order.m_orderRefNo << " " << order.m_side << " "
    << order.m_size << " " << order.m_price;
    return os;
}

std::ostream& operator << (std::ostream& os, const OutOrderExecuted& order) {
    os << order.m_msgType << " " << order.m_msgSize << "  "
       << order.m_ticker << " " << order.m_timestamp << " "
       << order.m_orderRefNo << " " << order.m_size << " " << order.m_price;
    return os;
}

std::ostream& operator << (std::ostream& os, const OutOrderReduced& order) {
    os << order.m_msgType << " " << order.m_msgSize << "  "
       << order.m_ticker << " " << order.m_timestamp << " "
       << order.m_orderRefNo << " " << order.m_sizeRemaining;
    return os;
}

std::ostream& operator << (std::ostream& os, const OutOrderReplaced& order) {
    os << order.m_msgType << " " << order.m_msgSize << "  "
       << order.m_ticker << " " << order.m_timestamp << " "
       << order.m_originalOrderRefNo << " " << order.m_newOrderRefNo
       << " " << order.m_newSize << " " << order.m_newPrice;
    return os;
}