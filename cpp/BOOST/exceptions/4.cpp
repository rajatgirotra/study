/* You can also augment your exception class using boost::tuple to add error_info objects together.
See below how it is done. */
#include <boost/exception/all.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <string>
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <stdexcept>
using std::string;
using std::cout;
using std::endl;

typedef boost::tuple <boost::errinfo_api_function, boost::errinfo_errno> exceptionDetail;

//Create your exception class.
struct file_open_error : public virtual boost::exception, public virtual std::exception {};

boost::shared_ptr<FILE> file_open(const char* file_name, const char* mode) {
    FILE* file = fopen(file_name, mode);
    if(file)
        return boost::shared_ptr<FILE>(file, fclose);
    else
        throw file_open_error() << boost::errinfo_file_name(file_name) << exceptionDetail("fopen", errno);
        //BOOST_THROW_EXCEPTION(file_open_error() << boost::errinfo_file_name(file_name) << exceptionDetail("fopen", errno));
}

int main() {
    try {
        file_open("NoFile", "rb");
    }catch(const boost::exception& e) {
        cout << boost::diagnostic_information(e) << endl;
    }
    return 0;
}

//BOOST_THROW_EXCEPTION is a very simple macro that prefixes information like file name, line and function name to the
//exception and then throws it. BUT PLEASE REMEMBER THAT YOUR EXCEPTION CLASS MUST DERIVE FROM BOTH boost::exception and
//std::exception classes. This information is then later printed when using the boost::diagnostic_information() function

