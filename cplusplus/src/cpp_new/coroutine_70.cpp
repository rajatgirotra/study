/* using co_yield to yield a value to coroutine caller */

#include <iostream>
#include <coroutine>
#include <exception>
#include <iterator>
#include <cassert>
using namespace std;

// we had CoroTask earlier. Now we create CoroGen as this will yield a value back to caller
template <typename T>
struct [[nodiscard]] Generator {
    struct promise_type {
        int m_value {};
        auto get_return_object() {
            return Generator{Generator::CoroHdl::from_promise(*this)};
        }

        auto initial_suspend() noexcept { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }

        void unhandled_exception() { std::terminate(); }
        void return_void() {}

        auto yield_value(int val) {
            m_value = val;
            return std::suspend_always{};
        }
    };
    using CoroHdl = std::coroutine_handle<promise_type>;
    private:
        CoroHdl m_handle;

    public:
        // ctor and dtor
        explicit Generator(auto handle) : m_handle(handle) {}
        ~Generator() {
            if(m_handle) {
                m_handle.destroy(); // must always destroy the coroutine frame on memory.
            }
        }    
        
        // disable copy and move to keep things simple
        Generator(const Generator&) = delete;
        Generator(Generator&&) = delete;

        bool resume() noexcept {
            // if handle is nullptr of if coroutine has already completed, return false.
            if(!m_handle || m_handle.done()) {
                return false;
            }

            // use the native coroutine API to resume the coroutine.
            m_handle.resume();
            return !m_handle.done();
        }

        auto getValue() {
            return m_handle.promise().m_value;
        }

        struct iterator {
            using iterator_category = std::input_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;
            private:
               Generator::CoroHdl m_handle;
            public:
               iterator(auto handle) : m_handle(handle) {}

               iterator operator ++() {
                   getNext();
                   return *this;
               }
               iterator operator++(int) {
                   return operator++();
               }

               void getNext() {
                   if(m_handle) {
                       m_handle.resume();
                       if(m_handle.done()) {
                           m_handle = nullptr; // set to nullptr so that getNext() will be no-op from next time
                       }
                   }
               }

               value_type operator*() const {
                   assert(m_handle != nullptr);
                   return m_handle.promise().m_value;
               }

               auto operator <=> (const iterator& rhs) const = default;
        };

        iterator begin() {
            if(!m_handle || m_handle.done()) {
                return iterator{nullptr};
            }
            iterator it(m_handle);
            it.getNext();
            return it;
        }

        iterator end() {
            return iterator{nullptr};
        }
};

Generator<int> coro(int max) {
    cout << "\tcoro() start\n";
    
    for(int value = 1; value <= max; ++value) {
        cout << "\tcoro() " << value << "/" << max << "\n";
        co_yield value;
    }
    
    cout << "\tcoro() end\n";
}

int main() {
    auto task = coro(5);
    cout << "Main: coro() created\n";

    // loop through coroutine until resume() is true
    for(auto&& value : task) {
        cout << "Main: coro() suspended with value: " << value << "\n";
    }
    cout << "Main: coro() done\n";
}

/* 
next, let's see how to use co_return.
Write a coroutine which takes a range and yields the value of each item in the range and then finally
co_returns the average of the items in the range (in double)
*/