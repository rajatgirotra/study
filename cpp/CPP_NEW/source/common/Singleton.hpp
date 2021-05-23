/** @file common/Singleton.hpp
 *  include this file to create Singleton objects.
 */
#pragma once

#include <cstdlib>

namespace cs {
    namespace common {
        /**
          * @brief template class to help create Singleton objects.
          *
          * to create Singleton class (say MySingleton), do:
          * @code
          * class MySingleton : public Singleton<MySingleton>
          * {
          *     friend class Singleton<MySingleton>;
          * }
          *
          * MySingleton& ref = MySingleton::instance();
          * @endcode
          */
        template <typename T>
        class Singleton {
        public:

            /**
             * @brief function to create and return and instance of type T.
             *
             * when instance() is first called, it will create a new object of type T by calling its default constructor;
             * subsequent calls to instance() will return the same object.\n
             * lifetime of the object returned by instance() is managed by the class itself. Do not call delete/free() on the
             * returned instance.\n
             * <b>this method can be safely called from within the destructor of static objects also. @emoji :smile: </b>
             *
             * <b>Thread-safety</b>\n
             * This method is thread-safe.
             *
             * @return an instance of a class T where T is the template argument.
             *
             * @sa common/Singleton.hpp
             */
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
