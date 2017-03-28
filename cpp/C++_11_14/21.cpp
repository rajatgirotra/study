/* C++11 introduces the concept of initializer list to make initialization of objects uniform.
 * Uptil now objects can be initialized using curly braces, round brackets. Now the standard wants to formalise all that.
 * An initializater list is just a comma separated list of values surrounding by curly braces and does vale initialisation.
 */
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    int32_t x {};
    cout << x << endl;

    int16_t* p {}; //initialised with nullptr

    int8_t* c{}; //same as above

    signed char* ch {c}; //nullptr

    int16_t arr[] {1, 2, 3, 4, 5};
    cout << "arr size: " << sizeof(arr)/sizeof(arr[0]) << endl;

    vector<string> v { "Rajat", "Ahmed" };
    cout << v[0] << "  " << v[1] << endl;

    int16_t i {5.3};  //WARNING, because of narrowing initialization, use -Wnarrowing
    cout << i << endl;
    return 0;
}
