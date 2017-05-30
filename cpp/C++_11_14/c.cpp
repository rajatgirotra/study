#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <iomanip>
using namespace std;

using t = std::tuple<int, float>;
using p = std::pair<int, float> p;

struct Foo
{
    Foo(std::tuple<int, float>);
};

int main()
{
    cout << boolalpha << std::is_convertible<t, Foo>::type::value << endl;
    return 0;
}
