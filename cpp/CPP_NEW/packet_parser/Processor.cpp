#include "Processor.hpp"
#include "Decoder.hpp"
#include <stdexcept>
#include <string>
#include <iostream>
#include <cstring>

constexpr std::uint32_t MSG_SZ_ADD = 34;
constexpr std::uint32_t MSG_SZ_EXECUTE = 21;
constexpr std::uint32_t MSG_SZ_CANCEL = 21;
constexpr std::uint32_t MSG_SZ_REPLACE = 33;

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
    InAddOrder addOrder{};
    Decoder::decode_addOrder(payload, addOrder);
    std::cout << addOrder << std::endl;
}

void Processor::processExecuteOrderMessage(char* payload, std::size_t payloadLen) {
    InOrderExecuted orderExecuted{};
    Decoder::decode_orderExecuted(payload, orderExecuted);
    std::cout << orderExecuted << std::endl;
}

void Processor::processCancelOrderMessage(char* payload, std::size_t payloadLen) {
    InOrderCancelled orderCancelled{};
    Decoder::decode_orderCancelled(payload, orderCancelled);
    std::cout << orderCancelled << std::endl;
}

void Processor::processReplaceOrderMessage(char* payload, std::size_t payloadLen) {
    InOrderReplaced orderReplaced{};
    Decoder::decode_orderReplaced(payload, orderReplaced);
    std::cout << orderReplaced << std::endl;
}
