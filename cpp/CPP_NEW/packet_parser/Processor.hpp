#pragma once

#include "InputFormat.hpp"
#include <array>
#include <cstdint>
#include <queue>
#include <cassert>
#include <memory>
#include <fstream>

class OrderManager;
class Processor {
    // should be sufficient to hold messages that straddle multiple UDP packets.
    std::array<char, (1<<16) + 100> m_buffer{};
    std::uint32_t m_bytesAvailable {0}; // number of bytes that can be consumed from the buffer.
    std::priority_queue<Packet, std::vector<Packet>, std::greater<Packet>> m_outOfSeqPkts {};
    std::uint32_t m_nextExpectedSeqNo {1};
    std::unique_ptr<OrderManager> m_orderManager;
    std::ofstream m_outFile;

public:

    Processor();
    ~Processor();

    std::uint32_t nextExpectedSeqNo() const noexcept { return m_nextExpectedSeqNo; }
    void nextExpectedSeqNo(std::uint32_t val) noexcept { m_nextExpectedSeqNo = val; }

    void queue(Packet&& pkt) { m_outOfSeqPkts.push(std::move(pkt)); }

    // return true if the sequence number of first out of sequence packet is same as next expected seq no
    bool hasNext() const noexcept {
        return !m_outOfSeqPkts.empty() && m_outOfSeqPkts.top().m_seqNo == m_nextExpectedSeqNo;
    }

    Packet getNext() noexcept;
    void processPacket(const Packet& pkt);
private:
    std::uint32_t doProcess(char* payload, std::size_t payloadLen);
    void processAddOrderMessage(char* payload, std::size_t payloadLen);
    void processExecuteOrderMessage(char* payload, std::size_t payloadLen);
    void processCancelOrderMessage(char* payload, std::size_t payloadLen);
    void processReplaceOrderMessage(char* payload, std::size_t payloadLen);
    template <std::size_t N> void write(const std::array<char, N>&);
};

template<std::size_t N>
inline void Processor::write(const std::array<char, N>& buffer) {
    m_outFile.write(buffer.data(), buffer.size());
}
