#pragma once

#include <cstdint>


struct Parser {
    static void onUDPPacket(char* buffer, std::uint16_t packetSize);
};