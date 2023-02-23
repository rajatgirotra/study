#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <boost/bind/bind.hpp>
#include <thread>
using namespace std;
namespace asio = boost::asio;

struct Printer {
    asio::io_context& m_io;
    asio::io_context::strand m_strand;
    asio::steady_timer m_timer_1;
    asio::steady_timer m_timer_2;
    int m_count {};

    Printer(asio::io_context& io) : m_io(io), m_strand(m_io), m_timer_1(m_io, asio::chrono::seconds(1)),
                                    m_timer_2(m_io, asio::chrono::seconds(1)), m_count(0) {
        m_timer_1.async_wait(asio::bind_executor(m_strand, boost::bind(&Printer::print_1, this, asio::placeholders::error)));
        m_timer_2.async_wait(asio::bind_executor(m_strand, boost::bind(&Printer::print_2, this, asio::placeholders::error)));
    }

    ~Printer() noexcept {
        cout << "Final count: " << m_count << endl;
    }

    void print_1(const boost::system::error_code& ec) {
        if(m_count < 10) {
            cout << "Timer 1 expired, count: " << m_count + 1 << endl;
            ++m_count;
            m_timer_1.expires_at(m_timer_1.expiry() + asio::chrono::seconds(1));
            m_timer_1.async_wait(asio::bind_executor(m_strand, boost::bind(&Printer::print_1, this, asio::placeholders::error)));
        }
    }

    void print_2(const boost::system::error_code& ec) {
        if(m_count < 10) {
            cout << "Timer 2 expired, count: " << m_count + 1 << endl;
            ++m_count;
            m_timer_2.expires_at(m_timer_2.expiry() + asio::chrono::seconds(1));
            m_timer_2.async_wait(asio::bind_executor(m_strand, boost::bind(&Printer::print_2, this, asio::placeholders::error)));
        }
    }
};

int main() {
    asio::io_context io;
    Printer p(io);

    std::thread t([&io]() {
        io.run();
    });

    io.run();

    t.join();
}

///*
// * You already know that an executor type implements how your completion handlers are queued and run.
// *
// * template <typename Executor>
// * class strand {}; // strand is a class which can take any executor type and serialize all the completion handlers for that executor type.
// *
// * How? basically if you see the io_context::basic_executor_type class, you will see that all public methods in that class like
// * context(), defer(), dispatch(), post(), execute(), on_work_finished(), on_work_started() etc. are also defined in asio::strand class.
// *
// * So we can just substitute the strand class where we need to provide an executor_type object.
// * To create strand objects. you can use the asio::make_strand() helper function. this helper function has 2 overloads. One take an executor_type
// * and the second takes an asio::execution_object.
// *
// * Now the asio::io_context itself derives from asio::execution_object, so we can create make_strand() by just passing the asio::io_context object.
// *
// * Remember that an asio::execution_context must define a nested typedef "executor_type". Since io_context derives from execution_context, it has this typedef
// * "typedef basic_executor_type<std::allocator<void>, 0> executor_type;"
// *
// * Another way is to use the asio::io_context::strand class itself instead of boost::asio::strand<Executor> class.
// */