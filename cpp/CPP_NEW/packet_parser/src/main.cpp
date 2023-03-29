#include "Parser.hpp"
#include <iostream>
#include <fstream>
#include <array>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Usage\n\t" << argv[0] << "<input.bin>\n";
        return -1;
    }
    ifstream ifs(argv[1], std::ios_base::in);
    if(!ifs.good()) {
        cout << "failed to open file " << argv[1] << " for reading\n";
        return -1;
    }

    std::array<char, 64> buffer{};
    Parser myParser;
    while (true) {
        ifs.read(buffer.data(), 2);
        if(!ifs.good()) {
            break;
        }
        uint16_t packetSize = htons(*reinterpret_cast<uint16_t*>(buffer.data()));
        ifs.read(buffer.data() + 2, packetSize-2);
        if(!ifs.good()) {
            cout << "failed to read UDP packet from input file\n";
            return -1;
        }
        myParser.onUDPPacket(buffer.data(), packetSize);
    }
    ifs.close();
    return 0;
}