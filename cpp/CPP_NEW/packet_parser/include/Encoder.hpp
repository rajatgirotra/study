#pragma once

#include <cstdint>
#include "OutputFormat.hpp"


struct Encoder {
private:
    static void encode_u16(char* start, std::uint16_t val);
    static void encode_u32(char* start, std::uint32_t val);
    static void encode_u64(char* start, std::uint64_t val);
    static void encode_s32(char* start, std::int32_t val);
    static void encode_r64(char* start, double val);
    static void encode_text(char* start, const char* source, std::size_t len);
    static int isBigEndian();

public:
    static void encode_addOrder(char* buffer, OutAddOrder& order);
    static void encode_orderExecuted(char* buffer, OutOrderExecuted& order);
    static void encode_orderReduced(char* buffer, OutOrderReduced& order);
    static void encode_orderReplaced(char* buffer, OutOrderReplaced& order);
};



