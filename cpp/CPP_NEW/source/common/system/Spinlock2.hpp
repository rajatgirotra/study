#pragma once

#include <atomic>
namespace cs {
    namespace common {
        namespace system {
            class Spinlock2 {
                std::atomic_flag m_flag = ATOMIC_FLAG_INIT; // must use ATOMIC_FLAG_INIT which initialzes m_flag to false; otherwise it is indeterminate.
//                std::atomic_flag m_flag {}; // with C++20, ATOMIC_FLAG_INIT is deprecated and by default m_flag is in clear state. i.e. false

            public:
                void lock() noexcept;
                void unlock() noexcept;
                bool try_lock() noexcept;
            };
        }
    }
}