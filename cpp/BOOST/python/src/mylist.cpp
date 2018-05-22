/* Please read 6_README.txt
 * Extract data from python list
 */


#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/extract.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct MyList {
std::string myMsg {};
public:
    void setMsg(boost::python::list msgs);

    std::string getMsg() const { return myMsg; }
};

void MyList::setMsg(boost::python::list msgs) {
    auto len = boost::python::len(msgs);
    std::stringstream ss;
    for(auto i = 0; i <len; ++i) {
        if(i > 0) ss << ", ";
        std::string msg = boost::python::extract<std::string>(msgs[i]);
        ss << msg;
    }
    myMsg = ss.str();
}

BOOST_PYTHON_MODULE(my_list_ext) {
    using namespace boost::python;
    class_<MyList>("MyList", "MyList class to test list passing from python to c++")
            .add_property("value", &MyList::getMsg, &MyList::setMsg);
}

/* Read scope.cpp and scope.py next */