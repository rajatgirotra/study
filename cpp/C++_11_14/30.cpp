/* It is possible with C++11 to declare typedef's to template classes.
 * Let's try it with regular c++ and see why we could not succeed
 */

#include <vector>
using namespace std;

//typedef vector<T, allocator<T> > Vector_t;
//You can't do the above unless you have decided what your parameter T actually is.

template <typename T> 
using Vec =  vector<T, allocator<T> >;
//However, this is possible in C++11, but you have to use the using directive instead of typedef... :-)

int main()
{
    Vec<int> intVec;
    return 0;
}
    
//Also, C++2003 doesnt allow template parameters to have defualt values in function templates.
//This is allowed in C++11 as we will later see.
