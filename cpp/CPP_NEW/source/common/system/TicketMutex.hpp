#pragma once
#include <atomic>

namespace cs {
    namespace common {
        namespace system {
            class TicketMutex {
                std::atomic_int m_in = ATOMIC_VAR_INIT(0); // a ticket number you get when you go to a bank
                std::atomic_int m_out = ATOMIC_VAR_INIT(0); // the current ticket number that is being served.

            public:
                void lock() noexcept;
                void unlock() noexcept;
                bool try_lock() noexcept;
            };
        }
    }
}