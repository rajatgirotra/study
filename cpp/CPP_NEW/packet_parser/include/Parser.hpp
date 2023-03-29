#pragma once

#include <cstdint>
#include <memory>

class Processor;

struct Parser {
    void onUDPPacket(char* buffer, std::uint16_t packetSize);

    Parser();
    ~Parser();
private:
    std::unique_ptr<Processor> m_processor;
};