#include <iostream>
using namespace std;

template <bool valid>
struct good
{
    typedef value; 
}

template <>
struct good<false>
{};

#define MY_STATIC_ASSERT2 (cond,text) \
    sizeof(good<cond>);

#define MY_STATIC_ASSERT(cond,text) \
    typedef char _my_assert_##text [(cond)?1:-1] ;

int main()
{
    MY_STATIC_ASSERT(false,Sorry);
}
