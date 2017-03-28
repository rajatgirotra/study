#include <iostream>
using namespace std;

template <bool b> struct msa_helper;
template <> struct msa_helper<true> {};
#define MY_STATIC_ASSERT(cond) \
    sizeof(msa_helper<bool(cond)>);

#define MY_ASSERT(cond, name) \
typedef char _my_assert##name [(cond) ? 1 : -1];

int main()
{
    MY_STATIC_ASSERT (false);
    MY_ASSERT (true, Sorry);
    MY_ASSERT (false, Sorry);
    return 0;
}

