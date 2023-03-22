#include <fcntl.h>
#include <unistd.h>
#include "Parser.hpp"
#include <cstdio>
#include <arpa/inet.h>
#include "OutputFormat.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <array>
#include <cassert>
#include "Encoder.hpp"

int main(int argc, char** argv) {
//    std::array<char, 7> buffer{};
//    buffer[0] = 0x0;
//    buffer[1] = 0x07;
//    buffer[2] = 0x0;
//    buffer[3] = 0x0;
//    buffer[4] = 0x0;
//    buffer[5] = 0x2;
//    buffer[6] = 0x37;
//
//    std::array<char, 7> buffer2{};
//    buffer2[0] = 0x0;
//    buffer2[1] = 0x07;
//    buffer2[2] = 0x0;
//    buffer2[3] = 0x0;
//    buffer2[4] = 0x0;
//    buffer2[5] = 0x1;
//    buffer2[6] = 0x38;
//
//
//    Parser::onUDPPacket(buffer.data(), 7);
//    Parser::onUDPPacket(buffer2.data(), 7);


    constexpr int currentDate = 20180612;
    Parser myParser;

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Couldn't open %s\n", argv[1]);
        return 1;
    }

    char bigbuf[5000];
    while (read(fd, bigbuf, 2) != 0) {
        uint16_t packetSize = htons(*(uint16_t *)bigbuf);
        read(fd, bigbuf + 2, packetSize - 2);
        myParser.onUDPPacket(bigbuf, packetSize);
    }

    close(fd);

    std::cout << sizeof(OutOrderReplaced) << std::endl;

    std::ofstream ofs("/tmp/abc.out", std::ios_base::trunc | std::ios_base::binary);

    assert(ofs.is_open());
    OutAddOrder outAddOrder;
    outAddOrder.m_timestamp = 0x0102030405060708;
    outAddOrder.m_orderRefNo = 0xABCDEF1009080705;
    outAddOrder.m_side = 'S';
    std::memcpy(outAddOrder.m_ticker, "SPY", 3);
    outAddOrder.m_size = 0x123;
    outAddOrder.m_price = 123.5;

    std::array<char, 44> outBuffer;
    Encoder::encode_addOrder(outBuffer.data(), outAddOrder);
    ofs.write(outBuffer.data(), sizeof(OutAddOrder));
    ofs.close();
    return 0;

}