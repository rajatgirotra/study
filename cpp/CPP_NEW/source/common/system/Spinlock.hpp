#pragma once

#include <atomic>
namespace cs {
    namespace common {
        namespace system {
            class Spinlock {
            private:
                std::atomic<bool> m_lock {false}; // false means lock is available.

            public:
                void lock() noexcept;

                void unlock() noexcept;

                bool try_lock() noexcept;
            };
        }
    }
}
