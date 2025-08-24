#if !defined(BOOST_PP_IS_ITERATING)

#define BOOST_PP_LIMIT_ITERATION 2
#define BOOST_PP_LIMIT_MAG 2
#include <boost/preprocessor/config/limits.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

#include <iostream>
using namespace std;

#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, 3, "pp_2.cpp"))
#include BOOST_PP_ITERATE()

int main() {
    cout << func_1() << endl;
    cout << func_2() << endl;
    cout << func_3() << endl;
}

#else
int BOOST_PP_CAT(func_,BOOST_PP_ITERATION())() { \
    return BOOST_PP_ITERATION_DEPTH(); \
}

#endif
