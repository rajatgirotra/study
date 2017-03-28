#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <ctime>

using namespace std;

template <typename Arg, typename Result>
struct unary_func {
    typedef Arg argument_type;
    typedef Result result_type;
};

template <typename Arg1, typename Arg2, typename Result>
struct binary_func {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

//Template class to convert a binary_function into a unary_function, by binding the first argument to a fixed value
template <typename Operation>
class myBinder1st : public unary_func < typename Operation::second_argument_type,
                                        typename Operation::result_type> {
    Operation op;
    typename Operation::first_argument_type value;

    public:
    //C'tor
    myBinder1st(const Operation& pOp, 
                const typename Operation::first_argument_type& x) : op(pOp), value(x) {
    }

    typename Operation::result_type operator() (const typename Operation::second_argument_type& arg) {
        return op(value, arg);
    }
};

//Convenience function to return an object of the above class.
template <typename Operation, typename T>
myBinder1st<Operation>  myBind1st(const Operation& op, const T& x) {
    return myBinder1st<Operation> (op, typename Operation::first_argument_type(x));
}


struct IsOdd : public unary_func<int, bool>
{
    bool operator()(const int& x) {
        if( x % 2 == 0)
            return false;
        else
            return true;
    }
};

struct Summation : public binary_func<int, int, int>
{
    int operator()(const int& x, const int& y) {
        return (x+y);
    }
};


int main() {
    IsOdd isOdd;

    Summation sum;
    Summation::first_argument_type  input1;
    Summation::second_argument_type input2;
    Summation::result_type resultSum;

    IsOdd::argument_type input;
    IsOdd::result_type result;

    result = isOdd(10);
    cout << "isOdd(10) = " << std::boolalpha << result << endl;

    result = isOdd(1);
    cout << "isOdd(1) = " << std::boolalpha << result << endl;

    input1 = 23;
    input2 = 98;
    resultSum = sum(input1, input2);
    cout << resultSum << endl;

    return 0;
}


