#include "Spinlock3.hpp"
namespace cs {
    namespace common {
        namespace system {

            void Spinlock3::lock() noexcept {
                while(!m_flag.test_and_set(std::memory_order_acquire)) {
                    m_flag.wait(true, std::memory_order_relaxed); // wait till m_flag != true. internally different compiler may use different kinds
                    // of wait mechanisms. futex, condition_variable, exponential backoff etc.
                }
            }

            void Spinlock3::unlock() noexcept {
                m_flag.clear(std::memory_order_release);
                m_flag.notify_one();
            }

            bool Spinlock3::try_lock() noexcept {
                return !m_flag.test(std::memory_order_relaxed) && !m_flag.test_and_set(std::memory_order_acquire);
            }
        }
    }
}

/*
 * this is a good spinlock. However, this version is not FAIR. which means if let's say thread1 comes and blocks on the spinlock.
 * followed by thread2. Now when the spinlock actually gets available, thread2 might beat thread1 to it.
 *
 * We want a version of spinlock which is FAIR. For that we come up with another mechanism called a ticket_mutex. the concept is vert simple.
 * just like you visit a bank and get a ticket number on entry and then wait for your turn for the teller/banker. exactly that.
 */