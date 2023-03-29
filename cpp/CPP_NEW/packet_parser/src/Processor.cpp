#include "Processor.hpp"
#include "Decoder.hpp"
#include "Encoder.hpp"
#include "OrderManager.hpp"
#include <algorithm>
#include <chrono>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cstring>

constexpr std::uint32_t MSG_SZ_ADD = 34;
constexpr std::uint32_t MSG_SZ_EXECUTE = 21;
constexpr std::uint32_t MSG_SZ_CANCEL = 21;
constexpr std::uint32_t MSG_SZ_REPLACE = 33;

Processor::Processor() : m_orderManager(new OrderManager), m_outFile("output.bin", std::ios_base::trunc | std::ios_base::binary) {
    assert(m_outFile.good() && m_outFile.is_open());
}

Processor::~Processor() {
    m_orderManager.reset();
    m_outFile.close();
}

Packet Processor::getNext() noexcept {
    assert(!m_outOfSeqPkts.empty());
    auto&& pkt = m_outOfSeqPkts.top();
    //hack as priority_queue doesn't support move only types during pop().
    Packet& ncPkt = const_cast<Packet&>(pkt);
    m_outOfSeqPkts.pop();
    return std::move(ncPkt);
}


void Processor::processPacket(const Packet& pkt) {
    std::uint32_t bytesConsumed {};
    // do we have any unconsumed bytes from last payload?
    if(m_bytesAvailable) {
        std::memcpy(m_buffer.data() + m_bytesAvailable, pkt.m_payload.data(), pkt.m_payloadSize);
        std::size_t sz = m_bytesAvailable + pkt.m_payloadSize;
        bytesConsumed = doProcess(m_buffer.data(), sz);
        if(sz == bytesConsumed) {
            m_bytesAvailable = 0;
        } else {
            m_bytesAvailable = sz - bytesConsumed;
            std::memmove(m_buffer.data(), m_buffer.data() + bytesConsumed, m_bytesAvailable);
        }
    } else {
        bytesConsumed = doProcess(const_cast<char*>(pkt.m_payload.data()), pkt.m_payloadSize);
        if(bytesConsumed != pkt.m_payloadSize) {
            m_bytesAvailable = pkt.m_payloadSize - bytesConsumed;
            std::memcpy(m_buffer.data(), pkt.m_payload.data() + bytesConsumed, m_bytesAvailable);
        }
    }
    ++this->m_nextExpectedSeqNo;
}

std::uint32_t Processor::doProcess(char* payload, std::size_t payloadLen) {
    std::uint32_t bytesConsumed{};
    bool done {false};
    while(!done && payloadLen > 0) {
        switch(payload[0]) {
            case 'A': {
                if (payloadLen >= MSG_SZ_ADD) {
                    processAddOrderMessage(payload, payloadLen);
                    payload += MSG_SZ_ADD;
                    bytesConsumed += MSG_SZ_ADD;
                    payloadLen -= MSG_SZ_ADD;
                } else { done = true; }
                break;
            }
            case 'E': {
                if (payloadLen >= MSG_SZ_EXECUTE) {
                    processExecuteOrderMessage(payload, payloadLen);
                    payload += MSG_SZ_EXECUTE;
                    bytesConsumed += MSG_SZ_EXECUTE;
                    payloadLen -= MSG_SZ_EXECUTE;
                } else { done = true; }
                break;
            }
            case 'X': {
                if (payloadLen >= MSG_SZ_CANCEL) {
                    processCancelOrderMessage(payload, payloadLen);
                    payload += MSG_SZ_CANCEL;
                    bytesConsumed += MSG_SZ_CANCEL;
                    payloadLen -= MSG_SZ_CANCEL;
                } else { done = true; }
                break;
            }
            case 'R': {
                if (payloadLen >= MSG_SZ_REPLACE) {
                    processReplaceOrderMessage(payload, payloadLen);
                    payload += MSG_SZ_REPLACE;
                    bytesConsumed += MSG_SZ_REPLACE;
                    payloadLen -= MSG_SZ_REPLACE;
                } else { done = true; }
                break;
            }
            default: {
                std::string errorStr{"failed to parse message with unknown message type "};
                errorStr.append(1, payload[0]);
                throw std::runtime_error(errorStr);
            }
        }
    }
    return bytesConsumed;
}

void Processor::processAddOrderMessage(char* payload, std::size_t payloadLen) {
    // decode Input Order
    InAddOrder addOrderIn{};
    Decoder::decode_addOrder(payload, addOrderIn);
//    std::cout << "IN: " << addOrderIn << std::endl;

    // cache it.
    m_orderManager->addOrder(addOrderIn);

    // process it
    OutAddOrder addOrderOut{};
    std::memcpy(addOrderOut.m_ticker, addOrderIn.m_ticker.data(),
                std::min(addOrderIn.m_ticker.size(), sizeof(addOrderOut.m_ticker)-1));
    addOrderOut.m_orderRefNo = addOrderIn.m_orderRefNo;
    addOrderOut.m_timestamp = std::chrono::nanoseconds(
            std::chrono::system_clock::now().time_since_epoch()).count();
    addOrderOut.m_side = (addOrderIn.m_side == Side::Sell ? 'S' : 'B');
    addOrderOut.m_size = addOrderIn.m_size;
    addOrderOut.m_price = static_cast<double>(addOrderIn.m_price)/10000.;

    // encode Output order
    std::array<char, sizeof(OutAddOrder)> buffer{};
    Encoder::encode_addOrder(buffer.data(), addOrderOut);

    // dump to output
    write(buffer);
//    std::cout << "OUT: " <<  addOrderOut << std::endl;
}

void Processor::processExecuteOrderMessage(char* payload, std::size_t payloadLen) {
    // decode OrderExecuted
    InOrderExecuted orderExecutedIn{};
    Decoder::decode_orderExecuted(payload, orderExecutedIn);
//    std::cout << "IN: " << orderExecutedIn << std::endl;

    // process execution
    InAddOrder& addOrderIn = m_orderManager->getOrder(orderExecutedIn.m_orderRefNo);
    addOrderIn.m_size -= orderExecutedIn.m_size;
    OutOrderExecuted orderExecutedOut{};
    std::memcpy(orderExecutedOut.m_ticker, addOrderIn.m_ticker.data(),
                std::min(addOrderIn.m_ticker.size(), sizeof(orderExecutedOut.m_ticker)-1));
    orderExecutedOut.m_timestamp = std::chrono::nanoseconds(
            std::chrono::system_clock::now().time_since_epoch()).count();
    orderExecutedOut.m_orderRefNo = addOrderIn.m_orderRefNo;
    orderExecutedOut.m_size = orderExecutedIn.m_size;
    orderExecutedOut.m_price = static_cast<double>(addOrderIn.m_price)/10000.;

    // encode Output order
    std::array<char, sizeof(OutOrderExecuted)> buffer{};
    Encoder::encode_orderExecuted(buffer.data(), orderExecutedOut);

    // dump to output
    write(buffer);
//    std::cout << "OUT: " << orderExecutedOut << std::endl;
}

void Processor::processCancelOrderMessage(char* payload, std::size_t payloadLen) {
    // decode OrderCancel
    InOrderCancelled orderCancelledIn{};
    Decoder::decode_orderCancelled(payload, orderCancelledIn);
//    std::cout << "IN: " << orderCancelledIn << std::endl;

    // process execution
    InAddOrder& addOrderIn = m_orderManager->getOrder(orderCancelledIn.m_orderRefNo);
    addOrderIn.m_size -= orderCancelledIn.m_size;
    OutOrderReduced orderReducedOut{};
    std::memcpy(orderReducedOut.m_ticker, addOrderIn.m_ticker.data(),
                std::min(addOrderIn.m_ticker.size(), sizeof(orderReducedOut.m_ticker)-1));
    orderReducedOut.m_timestamp = std::chrono::nanoseconds(
            std::chrono::system_clock::now().time_since_epoch()).count();
    orderReducedOut.m_orderRefNo = addOrderIn.m_orderRefNo;
    orderReducedOut.m_sizeRemaining = addOrderIn.m_size;

    // encode Output order
    std::array<char, sizeof(OutOrderReduced)> buffer{};
    Encoder::encode_orderReduced(buffer.data(), orderReducedOut);

    // dump to output
    write(buffer);
//    std::cout << "OUT: " << orderReducedOut << std::endl;
}

void Processor::processReplaceOrderMessage(char* payload, std::size_t payloadLen) {
    // decode OrderReplace
    InOrderReplaced orderReplacedIn{};
    Decoder::decode_orderReplaced(payload, orderReplacedIn);
//    std::cout << "IN: " << orderReplacedIn << std::endl;

    // process execution
    InAddOrder addOrderIn = m_orderManager->getOrder(orderReplacedIn.m_originalOrderRefNo);
    m_orderManager->eraseOrder(orderReplacedIn.m_originalOrderRefNo);
    addOrderIn.m_size = orderReplacedIn.m_size;
    addOrderIn.m_orderRefNo = orderReplacedIn.m_newOrderRefNo;
    addOrderIn.m_price = orderReplacedIn.m_price;
    // cache it.
    m_orderManager->addOrder(addOrderIn);

    OutOrderReplaced orderReplacedOut;
    std::memcpy(orderReplacedOut.m_ticker, addOrderIn.m_ticker.data(),
                std::min(addOrderIn.m_ticker.size(), sizeof(orderReplacedOut.m_ticker)-1));
    orderReplacedOut.m_timestamp = std::chrono::nanoseconds(
            std::chrono::system_clock::now().time_since_epoch()).count();
    orderReplacedOut.m_originalOrderRefNo = orderReplacedIn.m_originalOrderRefNo;
    orderReplacedOut.m_newOrderRefNo = orderReplacedIn.m_newOrderRefNo;
    orderReplacedOut.m_newSize = orderReplacedIn.m_size;
    orderReplacedOut.m_newPrice = static_cast<double>(orderReplacedIn.m_price)/10000.;

    // encode Output order
    std::array<char, sizeof(OutOrderReplaced)> buffer{};
    Encoder::encode_orderReplaced(buffer.data(), orderReplacedOut);

    // dump to output
    write(buffer);
//    std::cout << "OUT: " << orderReplacedOut << std::endl;
}
