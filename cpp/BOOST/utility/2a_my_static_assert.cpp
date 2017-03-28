#include <iostream>
using namespace std;

#define MY_ASSERT(cond, name) \
typedef char _my_assert_failure##name [(cond) ? 1 : -1]

template <bool x>
struct _my_second_assert;

template <>
struct _my_second_assert<true> { enum { value = 1 }; };

#define MY_SECOND_ASSERT(cond, name) \
sizeof(_my_second_assert<(bool)cond>);

int main()
{
    MY_ASSERT(true, Success);
    //MY_ASSERT(false, Fails);

    MY_SECOND_ASSERT(true, SUCCESS);
    MY_SECOND_ASSERT(false, FAILS);
    return 0;
}

