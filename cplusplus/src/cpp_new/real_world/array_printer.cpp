/*
 * Get an array and its size as parameters. print the size and the elements
 */

#include <iostream>
#include <string>

using namespace std;

namespace
{
    template <typename T, auto N>
    void array_printer(T(&arr)[N])
    {
        [&arr]<auto... Idx> (std::index_sequence<Idx...>) {
            cout << "array(" << sizeof...(Idx) << "): ";
            ((cout << (Idx > 0 ? ", " : "") << arr[Idx]), ...);
            cout << endl;
        } (std::make_index_sequence<N>{});
    }
}


int main()
{
    double d[] = {10, 20., 30.};
    array_printer(d);

    int arr_i[1] {42};
    array_printer(arr_i);

}