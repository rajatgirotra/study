#include "Spinlock2.hpp"
namespace cs {
    namespace common {
        namespace system {

            void Spinlock2::lock() noexcept {
                while(true) {
                    // assume lock is available
                    if(!m_flag.test_and_set(std::memory_order_relaxed)) {
                        return;
                    }
                    while(m_flag.test(std::memory_order_acquire)) {
                        // spin till m_flag is true
                        __builtin_ia32_pause(); // signal CPU that we are in a spin-wait loop
                    }
                }
            }

            void Spinlock2::unlock() noexcept {
                m_flag.clear(std::memory_order_release);
            }

            bool Spinlock2::try_lock() noexcept {
                return !m_flag.test(std::memory_order_relaxed) && !m_flag.test_and_set(std::memory_order_acquire);
            }
        }
    }
}

/*
 * this is a good spinlock. let's use Here we are using CPU pause instruction to signal CPU that we are in a spin-wait loop,
 * so CPU can perform some optimization to save power. and may be give another thread a chance to run.
 *
 * Next we can use a new version of Spinlock using C++20 wait()/notify_one() functions on atomics.
 */
