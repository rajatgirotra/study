#include "TicketMutex.hpp"

namespace cs {namespace common {namespace system {
    void TicketMutex::lock() noexcept {
        //get a ticket number.
        const auto my_ticket = m_in.fetch_add(1, std::memory_order_relaxed);
        auto current_ticket = m_out.load(std::memory_order_acquire);
        while(my_ticket != current_ticket) {
            m_out.wait(current_ticket, std::memory_order_relaxed);
            current_ticket = m_out.load(std::memory_order_acquire);
        }
    }

    void TicketMutex::unlock() noexcept {
        m_out.fetch_add(1, std::memory_order_release);
        m_out.notify_all();
    }

    bool TicketMutex::try_lock() noexcept {
        // To be implemented
        return false;
    }

}}}