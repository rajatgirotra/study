#ifndef _ALGOS_HPP_
#define _ALGOS_HPP_

#include <string>
#include <iomanip>
#include <iostream>
#include <boost/operators.hpp>

using std::string;
using std::ostream;

class Details : private boost::less_than_comparable<Details>, boost::equality_comparable<Details>
{
    string stringDetail;
    int intDetail;
    double doubleDetail;

    public:
        Details(const string& pStr = "", const int& pInt = 0, const double& pDouble = 0.0)
               : stringDetail(pStr), intDetail(pInt), doubleDetail(pDouble)
        {}

        template <typename T>
        friend bool comparator(const Details& lhs, const Details& rhs);

        friend bool operator == (const Details& lhs, const Details& rhs)
        {
            return (lhs.intDetail == rhs.intDetail);
            //return (lhs.stringDetail == rhs.stringDetail);
        }

        friend bool operator < (const Details& lhs, const Details& rhs)
        {
            return (lhs.intDetail < rhs.intDetail);
            //return (lhs.stringDetail < rhs.stringDetail);
        }

        friend ostream& operator << (ostream& os, const Details& rhs);
};

template<>
inline
bool comparator<string>(const Details& lhs, const Details& rhs)
{
    return lhs.stringDetail < rhs.stringDetail;
}

template<>
inline
bool comparator<int>(const Details& lhs, const Details& rhs)
{
    return lhs.intDetail < rhs.intDetail;
}

template<>
inline
bool comparator<double>(const Details& lhs, const Details& rhs)
{
    return lhs.doubleDetail < rhs.doubleDetail;
}

inline
ostream& operator << (ostream& os, const Details& rhs)
{
    os.setf(std::ios::adjustfield, std::ios::left);
    os << "   StringDetail: " << std::setw(10) << rhs.stringDetail
       << "   IntDetails: " << std::setw(6) << rhs.intDetail
       << "   DoubleDetail: " << std::setw(7) << rhs.doubleDetail;
    return os;
}


#endif // _ALGOS_HPP_
