//
// Created by rajatgirotra on 22/3/23.
//

#include "Encoder.hpp"
#include <cstring>
#include <string>
#include <algorithm>

std::uint64_t inLittleEndian(std::uint64_t val) {
    // TODO
    return val;
}
int Encoder::isBigEndian() {
    short x = 0x0001;
    return !*((char *) &x);
}

void Encoder::encode_u16(char *start, std::uint16_t val) {
    if (isBigEndian()) {
        val = ((val & 0x00FF) << 8 | ((val >> 8) & 0xFF));
    }
    std::memcpy(start, reinterpret_cast<void *>(&val), sizeof(uint16_t));
}

void Encoder::encode_u32(char *start, std::uint32_t val) {
    if (isBigEndian()) {
        uint32_t hi = ((val & 0xFF) << 8 | ((val >> 8) & 0xFF));
        val >>= 16;
        val &= 0xFFFF;
        uint32_t low = ((val & 0xFF) << 8 | ((val >> 8) & 0xFF));
        uint32_t val = hi << 16 | low;
    }
    std::memcpy(start, reinterpret_cast<void *>(&val), sizeof(uint32_t));
}

void Encoder::encode_u64(char *start, std::uint64_t val) {
    if (isBigEndian()) {
        val = inLittleEndian(val);
    }
    std::memcpy(start, reinterpret_cast<void *>(&val), sizeof(uint64_t));
}

void Encoder::encode_s32(char *start, std::int32_t val) {
    if (isBigEndian()) {
        int32_t hi = ((val & 0xFF) << 8 | ((val >> 8) & 0xFF));
        val >>= 16;
        val &= 0xFFFF;
        int32_t low = ((val & 0xFF) << 8 | ((val >> 8) & 0xFF));
        int32_t val = hi << 16 | low;
    }
    std::memcpy(start, reinterpret_cast<void *>(&val), sizeof(int32_t));
}

void Encoder::encode_r64(char *start, double val) { // 4 decimal places are implied.
    std::int64_t result = *(reinterpret_cast<std::int64_t *>(&val));
    if (isBigEndian()) {
        val = inLittleEndian(val);
    }
    std::memcpy(start, reinterpret_cast<void *>(&result), sizeof(int64_t));
}

void Encoder::encode_text(char *start, const char *source, std::size_t len) {
    std::memset(start, 0, len);
    std::memcpy(start, source, len);
}

void Encoder::encode_addOrder(char *buffer, OutAddOrder &order) {
    // assume buffer is big enough
    encode_u16(buffer, order.m_msgType);
    buffer += sizeof(order.m_msgType);

    encode_u16(buffer, order.m_msgSize);
    buffer += sizeof(order.m_msgSize);

    encode_text(buffer, order.m_ticker, sizeof(order.m_ticker));
    buffer += 8;

    encode_u64(buffer, order.m_timestamp);
    buffer += 8;

    encode_u64(buffer, order.m_orderRefNo);
    buffer += 8;

    std::memset(buffer, order.m_side, 1);
    buffer += 1;

    std::memset(buffer, 0, 3);
    buffer += 3; // for padding.

    encode_u32(buffer, order.m_size);
    buffer += 4;

    encode_r64(buffer, order.m_price);
    buffer += 8;
}

void Encoder::encode_orderExecuted(char *buffer, OutOrderExecuted &order) {
    // assume buffer is big enough
    encode_u16(buffer, order.m_msgType);
    buffer += sizeof(order.m_msgType);

    encode_u16(buffer, order.m_msgSize);
    buffer += sizeof(order.m_msgSize);

    encode_text(buffer, order.m_ticker, sizeof(order.m_ticker));
    buffer += 8;

    encode_u64(buffer, order.m_timestamp);
    buffer += 8;

    encode_u64(buffer, order.m_orderRefNo);
    buffer += 8;

    encode_u32(buffer, order.m_size);
    buffer += 4;

    encode_r64(buffer, order.m_price);
    buffer += 8;
}

void Encoder::encode_orderReduced(char *buffer, OutOrderReduced &order) {
    // assume buffer is big enough
    encode_u16(buffer, order.m_msgType);
    buffer += sizeof(order.m_msgType);

    encode_u16(buffer, order.m_msgSize);
    buffer += sizeof(order.m_msgSize);

    encode_text(buffer, order.m_ticker, sizeof(order.m_ticker));
    buffer += 8;

    encode_u64(buffer, order.m_timestamp);
    buffer += 8;

    encode_u64(buffer, order.m_orderRefNo);
    buffer += 8;

    encode_u32(buffer, order.m_sizeRemaining);
    buffer += 4;
}

void Encoder::encode_orderReplaced(char *buffer, OutOrderReplaced &order) {
    // assume buffer is big enough
    encode_u16(buffer, order.m_msgType);
    buffer += sizeof(order.m_msgType);

    encode_u16(buffer, order.m_msgSize);
    buffer += sizeof(order.m_msgSize);

    encode_text(buffer, order.m_ticker, sizeof(order.m_ticker));
    buffer += 8;

    encode_u64(buffer, order.m_timestamp);
    buffer += 8;

    encode_u64(buffer, order.m_originalOrderRefNo);
    buffer += 8;

    encode_u64(buffer, order.m_newOrderRefNo);
    buffer += 8;

    encode_u32(buffer, order.m_newSize);
    buffer += 4;

    encode_r64(buffer, order.m_newPrice);
    buffer += 8;
}
