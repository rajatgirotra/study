/* Next is that how you can use boost::exception with some of the existing exception heirarchies. */
// Let us consider std::range_error class. boost provides you a function template called enable_error_info which basically takes one argument of your exception class and
// returns you an object that derives from both boost::exception and std::range_error. So you can upcast to boost::exception.

#include <stdexcept>
#include <boost/exception/all.hpp>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

typedef boost::error_info<struct tag_std_range_min, size_t> std_range_min;
typedef boost::error_info<struct tag_std_range_max, size_t> std_range_max;
typedef boost::error_info<struct tag_std_range_index, size_t> std_range_indx;

template <typename T>
class container {
    private:
        static const size_t SIZE = 20;
        T arr[SIZE];
    public:

       size_t size() const {
           return SIZE;
       }

       T& operator[] (int index) {
           if(index >= size()) {
               throw boost::enable_error_info(std::range_error("Index out of range")) << std_range_min(0)
                                                                  << std_range_max(size())
                                                                  << std_range_indx(index);
           }

            return arr[index];
      }

};

int main() {
    container<char> strCont;

    try {
        strCont[3] = 'A';
        strCont[30] = 'A';
    }catch(const boost::exception& e) {
        cout << boost::diagnostic_information(e) << endl;
    }

    return 0;
}
