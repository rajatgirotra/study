#include "exception.hpp"
#include <iostream>
using namespace std;

int main()
{
    try {
        common::framework::exception::io_error io;
        THROW_EXCEPTION(std::range_error("range_error"));
    } catch(const boost::exception& e) {
        cout << boost::diagnostic_information(e);
    }
};

