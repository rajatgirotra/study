#include "Spinlock.hpp"
#include <iostream>
namespace cs {
    namespace common {
        namespace system {

            void Spinlock::lock() noexcept {
                // assume lock is available. if not go around in a loop
                while(true) {
                    if(!m_lock.exchange(true, std::memory_order_acquire)) {
                        return; // we got the lock.
                    }
                    while(m_lock.load(std::memory_order_relaxed)) {
                        // pause
                        asm volatile ("pause");
                    }
                }
            }

            void Spinlock::unlock() noexcept {
                m_lock.store(false, std::memory_order_release);
            }

            bool Spinlock::try_lock() noexcept {
                return !m_lock.load(std::memory_order_relaxed) && !m_lock.exchange(true, std::memory_order_acquire) ;
            }
        }
    }
}
