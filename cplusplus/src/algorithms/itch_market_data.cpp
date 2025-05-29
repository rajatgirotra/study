#include <iostream>
#include <cstdint>
#include <fstream>
#include <memory>
using namespace std;

enum struct Side : char {
    BUY = 0x01,
    SELL = 0x02
};

constexpr char AddOrderMessageType = 'A';
constexpr char CancelOrderMessageType = 'C';

template<char MsgType> const char * const TypeTag = nullptr;
template<> const char * const TypeTag<AddOrderMessageType> = "ADD";
template<> const char * const TypeTag<CancelOrderMessageType> = "CANCEL";

template<char MsgType>
constexpr size_t MessageLen = -1;
template<>
constexpr size_t MessageLen<AddOrderMessageType> = 36;
template<>
constexpr size_t MessageLen<CancelOrderMessageType> = 23;

struct AddOrderMessage {
    char messageType;
    uint16_t stockLocate;
    uint64_t timestamp;
    uint64_t orderReferenceNumber;
    char buySellIndicator;
    uint32_t shares;
    uint32_t price;
};

template<typename OutStream>
inline OutStream &operator <<(OutStream &os, const AddOrderMessage &m) {
    os << TypeTag<AddOrderMessageType> <<
            " type " << m.messageType <<
            " stockLocate " << m.stockLocate <<
            " timestamp " << m.timestamp <<
            " orderReferenceNumber " << m.orderReferenceNumber <<
            " buySellIndicator " << static_cast<char>(m.buySellIndicator) <<
            " shares " << m.shares <<
            " price " << m.price;
    return os;
}

auto deleter = [](std::ifstream *f) {
    if (f) {
        f->close();
        delete f;
    }
};

class Reader {
private:
    std::unique_ptr<std::ifstream, decltype(deleter)> m_file;
    char m_buffer[1024];

public:
    Reader(const char* filename, [[maybe_unused]] size_t BUFFER_SIZE = 1024) : m_file(new std::ifstream(filename, ios_base::binary), deleter) {
        if (!m_file->is_open()) {
            throw std::runtime_error("failed to open file" + std::string(filename));
        }
    }
};

void process(const char* filename) {
    ifstream ifs(filename, std::ios_base::binary);
    if (!ifs) {
        throw std::invalid_argument("unable to open input file [" + std::string(filename) + "] for reading. please check file path and file permissions");
    }

    char buffer[100]{};
    while (ifs.good()) {
        ifs.read(buffer, 100);
    }
}

int main() {
    const char* filename = "/home/rajatgirotra/Downloads/random_file.bin";
    process(filename);
}