#pragma once

#include <cstdint>
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::int32_t;

class Packet; // forward declarations
class InAddOrder;
class InOrderExecuted;
class InOrderCancelled;
class InOrderReplaced;

struct Decoder {
    static void decode_u16(char* start, uint16_t& result);
    static void decode_u32(char* start, uint32_t& result);
    static void decode_s32(char* start, int32_t& result);
    static void decode_u64(char* start, uint64_t& result);

    static void decode_packet(char* start, Packet& pkt);
    static void decode_addOrder(char* start, InAddOrder& order);
    static void decode_orderExecuted(char* start, InOrderExecuted& order);
    static void decode_orderCancelled(char* start, InOrderCancelled& order);
    static void decode_orderReplaced(char* start, InOrderReplaced& order);
};
