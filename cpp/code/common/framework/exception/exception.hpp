#include <boost/exception/all.hpp>
#include <exception>
#include <string>

namespace common {
    namespace framework {
        namespace exception {
   
    typedef boost::error_info<struct tag_context, std::string> error_context;
    struct exception_base : virtual boost::exception, virtual std::exception {};
    struct io_error : virtual exception_base {};

    struct demangle_exception : virtual exception_base {};
} } } //end of namespace common::framework::exception


#define THROW_EXCEPTION(ExceptionObject) \
    BOOST_THROW_EXCEPTION(ExceptionObject);



