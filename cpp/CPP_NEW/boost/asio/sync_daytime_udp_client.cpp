#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <ctime>
#include <string>
#include <array>
using namespace std;
namespace asio = boost::asio;

int main(int argc, char** argv) {
    if(argc != 2) {
        cout << "Usage:\n\t" << argv[0] << " <HOST>\n";
        return 1;
    }

    asio::io_context io;
    asio::ip::udp::resolver resolver(io);

    auto endpoints = resolver.resolve(asio::ip::udp::v4(), "", "7777");
//    auto endpoints = resolver.resolve(asio::ip::udp::v4(), argv[1], "daytime");
    if(endpoints.size() == 0) {
        cout << "Unable to resolve udp daytime service.\n";
        return 1;
    }
    asio::ip::udp::endpoint receiver_endpoint = *(endpoints.begin());
    cout << receiver_endpoint.address().to_string() << ", " << receiver_endpoint.port() << endl;

    //1. send a connect to daytime server
    std::array<char, 1> buf {{0}};
    asio::ip::udp::socket socket(io);
    socket.open(asio::ip::udp::v4());

    socket.send_to(asio::buffer(buf), receiver_endpoint);

    // wait for reply from server
    std::array<char, 128> buffer{};
    asio::ip::udp::endpoint sender_endpoint{};
    boost::system::error_code ec{};
    size_t len = socket.receive_from(asio::buffer(buffer), sender_endpoint);

    std::cout.write(buffer.data(), len);
}