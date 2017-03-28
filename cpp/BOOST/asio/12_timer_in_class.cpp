/*
This is similar to 11_argument_binding.cpp
However, here we have the io_service object and the timer object in a class.
*/
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <chrono>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::asio;

class Printer
{
private:
    io_service m_io;
    high_resolution_timer m_timer;
    int m_count;

public:
    Printer() : m_timer(m_io, std::chrono::seconds(1)),
                m_count(0)
    {
        m_timer.async_wait(boost::bind(&Printer::print,
                                       this,
                                       boost::asio::placeholders::error));
        m_io.run();
    }

    ~Printer()
    {
        cout << "Final count is: " << m_count << endl;
    }
            

    void print(const boost::system::error_code& ec)
    {
        if(ec != boost::asio::error::operation_aborted)
        {
            if(m_count < 5)
            {
                cout << "Hello World: " << m_count << endl;
                ++m_count;
                m_timer.expires_at(m_timer.expires_at() + std::chrono::seconds(1));
                m_timer.async_wait(boost::bind(&Printer::print, this, boost::asio::placeholders::error));
            }
        }
    }
};

int main(int argc, char *argv[])
{
    Printer p;
    return 0;
}

