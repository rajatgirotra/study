#include "Processor.hpp"
#include "DecoderUtils.hpp"
#include <stdexcept>
#include <string>
#include <iostream>

void Processor::parsePacket(const Packet& pkt) {
    auto packet_type = pkt.m_payload[0];
    switch(packet_type) {
        case 'A': {
            InAddOrder addOrder{};
            DecoderUtil::decode_addOrder(const_cast<char*>(pkt.m_payload.data()), addOrder);
            std::cout << addOrder << std::endl;
            //TODO
            break;
        }
        case 'E': {
            InOrderExecuted orderExecuted{};
            DecoderUtil::decode_orderExecuted(const_cast<char*>(pkt.m_payload.data()), orderExecuted);
            std::cout << orderExecuted << std::endl;
            //TODO
            break;
        }
        case 'X': {
            InOrderCancelled orderCancelled{};
            DecoderUtil::decode_orderCancelled(const_cast<char*>(pkt.m_payload.data()), orderCancelled);
            std::cout << orderCancelled << std::endl;
            //TODO
            break;
        }
        case 'R': {
            InOrderReplaced orderReplaced{};
            DecoderUtil::decode_orderReplaced(const_cast<char*>(pkt.m_payload.data()), orderReplaced);
            std::cout << orderReplaced << std::endl;
            //TODO
            break;
        }
        default:
            std::string errorStr{"failed to parse UDP packet with unknown message type "};
            errorStr.append(1, packet_type);
            throw std::runtime_error(errorStr);
    }
    ++this->m_nextExpectedSeqNo;
}
