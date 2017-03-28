/*
In 12_timer_in_class and 11_argument_binding.cpp we create called io_service::run() from single thread
so all handlers ran sequentially.
Here we do the same but we use io_service::strand class.
*/
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <boost/bind.hpp>
#include <chrono>
#include <thread>

using namespace std;
using namespace boost::asio;

class Printer
{
private:
    high_resolution_timer m_timer1;
    high_resolution_timer m_timer2;    
    int m_count;
    io_service::strand m_strand;

public:
    Printer(boost::asio::io_service& io) : m_timer1(io, std::chrono::seconds(1)),
                                           m_timer2(io, std::chrono::seconds(1)),
                                           m_count(0),
                                           m_strand(io)
    {
        m_timer1.async_wait(m_strand.wrap(boost::bind(&Printer::print1,
                                                     this,
                                                     boost::asio::placeholders::error)));
        m_timer2.async_wait(m_strand.wrap(boost::bind(&Printer::print2,
                                                     this,
                                                     boost::asio::placeholders::error)));        
    }

    ~Printer()
    {
        cout << "Final count: " << m_count << endl;
    }

    void print1(const boost::system::error_code& ec)
    {
        if(ec != boost::asio::error::operation_aborted)
        {
            if(m_count < 10)
            {
                cout << "Timer 1: count = " << m_count << endl;
                ++m_count;
                m_timer1.expires_at(m_timer1.expires_at() + std::chrono::seconds(1));
                m_timer1.async_wait(m_strand.wrap(boost::bind(&Printer::print1,
                                                             this,
                                                             boost::asio::placeholders::error)));
            }
        }
    }

    void print2(const boost::system::error_code& ec)
    {
        if(ec != boost::asio::error::operation_aborted)
        {
            if(m_count < 10)
            {
                cout << "Timer 2: count = " << m_count << endl;
                ++m_count;
                m_timer2.expires_at(m_timer2.expires_at() + std::chrono::seconds(1));
                m_timer2.async_wait(m_strand.wrap(boost::bind(&Printer::print2,
                                                             this,
                                                             boost::asio::placeholders::error)));
            }
        }
    }
};

int main(int argc, char *argv[])
{
    boost::asio::io_service io;
    Printer p(io);
    std::thread t(boost::bind(&boost::asio::io_service::run,
                              &io));
    io.run();
    t.join();
    return 0;
}

