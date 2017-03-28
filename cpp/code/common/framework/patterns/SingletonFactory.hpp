#ifndef _COMMON_FRAMEWORK_DETAIL_SINGLETONFACTORY_HPP_
#define _COMMON_FRAMEWORK_DETAIL_SINGLETONFACTORY_HPP_

namespace common {
    namespace framework {
        namespace pattern {
            namespace detail {

    /** \brief Brief Description.\n
     *         Used to create an instance of the class represented by the template parameter _T
     */
    template <typename _T>
    struct SingletonFactory {

        /** Returns an instance of the  represented by the template parameter _T */
        static _T* create() { return new _T(); }

        /** deletes the instance of the represented by the template parameter _T 
         * @param[in] _poT a pointer to an object of class represented by the template parameter _T
         */
        static void destroy(_T* _poT) { delete _poT; }
    };

 
} } } } // end of namespace common::framework::pattern::detail

#endif // _COMMON_FRAMEWORK_DETAIL_SINGLETONFACTORY_HPP_
