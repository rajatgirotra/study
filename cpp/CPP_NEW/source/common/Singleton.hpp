/**
 * @brief template Singleton class to help create one and only one instance of a class.
 *
 * Singleton<T> is very trivial.
 */

#pragma once

#include <cstdlib>

namespace cs {
    namespace common {
        template <typename T>
        class Singleton {
        public:
            static T& instance();

            // disable copy constructor and assignments
            Singleton(const Singleton&) = delete;
            Singleton(Singleton&&) = delete;
            void operator = (const Singleton&) = delete;
            void operator = (Singleton&&) = delete;

            // destructor
            ~Singleton();

        protected:
            Singleton() = default;
        private:
            static void destroy() {
                m_instance->~T();
            }
            static bool m_destroyed;
            static T* m_instance;
        };

        template <typename T>
        bool Singleton<T>::m_destroyed {false};

        template <typename T>
        T* Singleton<T>::m_instance {nullptr};

        template <typename T>
        inline T& Singleton<T>::instance() {
            static T object;
            if(m_destroyed) {
                m_instance = new(&object) T;
                m_destroyed = false;
                std::atexit(Singleton<T>::destroy);
            }
            return object;
        }

        template <typename T>
        inline Singleton<T>::~Singleton() {
            m_destroyed = true;
        }
    }
}
