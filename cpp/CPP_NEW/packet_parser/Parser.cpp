#include "Parser.hpp"
#include "InputFormat.hpp"
#include "Decoder.hpp"
#include "Processor.hpp"
#include <iostream>

Parser::Parser() : m_processor(std::make_unique<Processor>()){
}

Parser::~Parser() {
    m_processor.reset();
}

void Parser::onUDPPacket(char* buffer, uint16_t packetSize) {
    try {
        // decode UDP packet
        Packet pkt;
        Decoder::decode_packet(buffer, pkt);

        // ignore duplicate and empty packets
        if(pkt.m_seqNo < m_processor->nextExpectedSeqNo() || pkt.m_payloadSize == 0) {
            std::cout << "Ignoring duplicate/empty udp packet with sequence no: " << pkt.m_seqNo << std::endl;
            return;
        }

        // queue packet
        m_processor->queue(std::move(pkt));

        // parse packets
        while(m_processor->hasNext()) {
            Packet&& packet = m_processor->getNext();
            m_processor->processPacket(packet);
        }
    } catch(const std::exception& e) {
        std::cout << "onUDPPacket failed with exception: " << e.what() << std::endl;
    } catch(...) {
        std::cout << "onUDPPacket failed with unknown exception" << std::endl;
    }
}
