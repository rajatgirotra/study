#include "Parser.hpp"
#include "InputFormat.hpp"
#include "Decoder.hpp"
#include "Processor.hpp"
#include <iostream>


void Parser::onUDPPacket(char* buffer, uint16_t packetSize) {
    static Processor processor;
    try {
        // decode packet
        Packet pkt;
        Decoder::decode_packet(buffer, pkt);

        // ignore duplicate and empty packets
        if(pkt.m_seqNo < processor.nextExpectedSeqNo() || pkt.m_payloadSize == 0) {
            std::cout << "Ignoring duplicate/empty packet with sequence no: " << pkt.m_seqNo << std::endl;
            return;
        }

        // queue packet
        processor.queue(std::move(pkt));

        // parse packets
        while(processor.hasNext()) {
            Packet&& packet = processor.getNext();
            processor.parsePacket(packet);
        }
    } catch(const std::exception& e) {
        std::cout << "parseUDPPacket failed with exception: " << e.what() << std::endl;
    } catch(...) {
        std::cout << "parseUDPPacket failed with unknown exception" << std::endl;
    }
}
