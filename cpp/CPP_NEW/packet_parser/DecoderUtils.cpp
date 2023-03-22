#include "DecoderUtils.hpp"
#include "InputFormat.hpp"
#include <arpa/inet.h>
#include <cstring>

void DecoderUtil::decode_u16(char *start, uint16_t &result) {
    result = ntohs(*reinterpret_cast<uint16_t *>(start));
}

void DecoderUtil::decode_u32(char *start, uint32_t &result) {
    result = ntohl(*reinterpret_cast<uint32_t *>(start));
}

void DecoderUtil::decode_s32(char *start, int32_t &result) {
    result = ntohl(*reinterpret_cast<int32_t *>(start));
}

void DecoderUtil::decode_u64(char *start, uint64_t &result) {
    result = *reinterpret_cast<uint64_t *>(start);
    result = static_cast<uint64_t>(ntohl(result & 0x00000000FFFFFFFFULL)) << 32 |
             ntohl((result & 0xFFFFFFFF00000000ULL) >> 32);
}

void DecoderUtil::decode_packet(char *start, Packet &pkt) {
    decode_u16(start, pkt.m_size);
    decode_u32(start + 2, pkt.m_seqNo);
    pkt.m_payloadSize = pkt.m_size - 6;
    if (pkt.m_payloadSize > 0) {
        std::memcpy(pkt.m_payload.data(), start + 6, pkt.m_payloadSize);
    }
}

void DecoderUtil::decode_addOrder(char *start, InAddOrder &order) {
    // skip msgType
    ++start;

    // timestamp
    decode_u64(start, order.m_timestamp);
    start += sizeof(InAddOrder::m_timestamp);

    // orderRefNo
    decode_u64(start, order.m_orderRefNo);
    start += sizeof(InAddOrder::m_orderRefNo);

    // side
    order.m_side = (*start == 'B' ? Side::Buy : Side::Sell);
    ++start;

    // size
    decode_u32(start, order.m_size);
    start += sizeof(InAddOrder::m_size);

    // ticker
    std::memcpy(order.m_ticker, start, 8);
    start += 8;
    char* pos = std::strchr(order.m_ticker, ' ');
    if(pos != nullptr) { *pos = '\0'; }

    // price
    decode_s32(start, order.m_price);
    start += sizeof(InAddOrder::m_price);
}

void DecoderUtil::decode_orderExecuted(char *start, InOrderExecuted &order) {
    // skip msgType
    ++start;

    // timestamp
    decode_u64(start, order.m_timestamp);
    start += sizeof(InOrderExecuted::m_timestamp);

    // orderRefNo
    decode_u64(start, order.m_orderRefNo);
    start += sizeof(InOrderExecuted::m_orderRefNo);

    // size
    decode_u32(start, order.m_size);
    start += sizeof(InOrderExecuted::m_size);
}

void DecoderUtil::decode_orderCancelled(char *start, InOrderCancelled &order) {
    // skip msgType
    ++start;

    // timestamp
    decode_u64(start, order.m_timestamp);
    start += sizeof(InOrderCancelled::m_timestamp);

    // orderRefNo
    decode_u64(start, order.m_orderRefNo);
    start += sizeof(InOrderCancelled::m_orderRefNo);

    // size
    decode_u32(start, order.m_size);
    start += sizeof(InOrderCancelled::m_size);
}

void DecoderUtil::decode_orderReplaced(char *start, InOrderReplaced &order) {
    // skip msgType
    ++start;

    // timestamp
    decode_u64(start, order.m_timestamp);
    start += sizeof(InOrderReplaced::m_timestamp);

    // originalOrderRefNo
    decode_u64(start, order.m_originalOrderRefNo);
    start += sizeof(InOrderReplaced::m_originalOrderRefNo);

    // newOrderRefNo
    decode_u64(start, order.m_newOrderRefNo);
    start += sizeof(InOrderReplaced::m_newOrderRefNo);

    // size
    decode_u32(start, order.m_size);
    start += sizeof(InOrderReplaced::m_size);

    // price
    decode_s32(start, order.m_price);
    start += sizeof(InOrderReplaced::m_price);
}

