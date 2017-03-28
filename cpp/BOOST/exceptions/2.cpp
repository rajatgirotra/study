#include <iostream>
#include <string>
#include <boost/exception/all.hpp>
#include <stdexcept>
using std::string;
using std::cout;
using std::endl;

//Create a typedef of boost::error_info template class. This is for ease of use.
//template <typename Tag, typename T> //The first template argument is just a unique identifier.
//class error_info;
typedef boost::error_info<struct tag_my_info_int, int> my_info_int; //template argument T defines the type of data you will augment your exception class with.
typedef boost::error_info<struct tag_my_info_string, string> my_info_string; //template argument T defines the type of data you will augment your exception class with.

//Create your exception class which derives from boost::exception
//Virtual so that you avoid ambiguity issues in case of multiple inheritance.
struct my_error : public virtual boost::exception, public virtual std::exception {
    void f() {
        throw my_error() << my_info_int(42); //You augment your exception class with the << operator
        // Also see how my_info object is created using an argument of type T.
    }

    void g() {
        try {
            f();
        } catch (const boost::exception& e) { //See how good is this. You are only catching a generic exception.
            //Further augment your exception class.
            e << my_info_string("ABC");

            //Now that we have augmented a couple of things, let us try to
            //retrieve it.
            const int* err_int = boost::get_error_info<my_info_int>(e);
            if(err_int)
                cout << "Error int = " << *err_int << endl;;

            const std::string* err_str = boost::get_error_info<my_info_string>(e);
            if(err_str)
                cout << "Error str = " << *err_str << endl;
        }
    }
};

int main() {
    my_error o;
    o.g();
}
