/*
 * Implementation of the double checked locking singleton design pattern; with the benefits of C++11 memory model
 */

#ifndef _COMMON_FRAMEWORK_SINGLETON_HPP_
#define _COMMON_FRAMEWORK_SINGLETON_HPP_

#include <atomic>
#include <mutex>
#include <cstdlib>
#include "SingletonFactory.hpp"

using common::framework::pattern::detail::SingletonFactory;

namespace common
{
    namespace framework
    {
        namespace pattern
        {

            /**
             * \brief Brief description.\n
             *            Singleton template class to restrict a given class (_T template parameter) from making multiple objects.
             *
             * Sample usage: To make a Singleton class A, do\n
             *
             * class A\n
             * {\n
             *     static A* getInstance()\n
             *     {\n
             *         return Singleton<A>::getInstance();\n
             *     }\n
             *     friend class SingletonFactory<A>;\n
             * };\n
             *
             * The SingletonFactory class calls the default constructor for class A to create the singleton object.\n
             * If class A does not have a default constructor, then you need to provide\n
             * your own implementation of the create() method to call the desired constructor for class A.\n
             * Also you need to provide an implementation of the destroy() method.\n
             */
            template <typename _T,
                     typename _SingletonFactory = SingletonFactory<_T>>
            class Singleton// : public common::framework::utils::call_traits<_T>
            {
                private:
                    typedef _T value_type;

                    static std::atomic<_T*> m_poInstance;
                    static std::mutex       m_mutex;
                    static bool             m_destroyed;

                    //disable copy construction and assignment
                    Singleton(const Singleton&) = delete;
                    Singleton& operator = (const Singleton&) = delete;

                    // destroys the singleton object of template type _T.
                    static void removeInstance();

                public:
                    /** returns a pointer to an object of template type _T. */
                    static value_type* getInstance(); //!< value_type is same as _T

            };

            //Define the class statics.
            template <typename _T, typename _SingletonFactory>
            std::atomic<_T*> Singleton<_T, _SingletonFactory>::m_poInstance {}; //initialized with nullptr

            template <typename _T, typename _SingletonFactory>
            std::mutex Singleton<_T, _SingletonFactory>::m_mutex;

            template <typename _T, typename _SingletonFactory>
            bool Singleton<_T, _SingletonFactory>::m_destroyed = false;

            template <typename _T, typename _SingletonFactory>
            _T* Singleton<_T, _SingletonFactory>::getInstance()
            {
                //Load m_poInstance
                value_type* poTemp = m_poInstance.load(std::memory_order_acquire);

                if(nullptr == poTemp)
                {
                    std::lock_guard<std::mutex> oLock(m_mutex);
                    //Load again. Traditional DCLP.
                    poTemp = m_poInstance.load(std::memory_order_relaxed);

                    if(nullptr == poTemp)
                    {
                        poTemp = _SingletonFactory::create();
                        //Store m_poInstance
                        m_poInstance.store(poTemp, std::memory_order_release);
                        //Cleanup at exit.
                        std::atexit(&Singleton<_T, _SingletonFactory>::removeInstance);
                    }
                }

                return poTemp;
            }

            template <typename _T, typename _SingletonFactory>
            void Singleton<_T, _SingletonFactory>::removeInstance()
            {
                //Load m_poInstance
                value_type* poTemp = m_poInstance.load(std::memory_order_acquire);

                if(nullptr != poTemp)
                {
                    std::lock_guard<std::mutex> oLock(m_mutex);
                    poTemp = m_poInstance.load(std::memory_order_relaxed);

                    if(nullptr != poTemp)
                    {
                        _SingletonFactory::destroy(poTemp);
                        m_destroyed = true;
                        m_poInstance.store(nullptr, std::memory_order_release);
                    }
                }
            }
} } } // end of namespace common::framework::pattern


#endif // _COMMON_FRAMEWORK_SINGLETON_HPP_
