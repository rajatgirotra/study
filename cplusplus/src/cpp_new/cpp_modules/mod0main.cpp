#include <iostream>

import Square; // import module “Square”

int main()
{
    Square x = toSquare(42);
    std::cout << x.getValue() << '\n';

    // const Data& d = x.getData(); // error. Data is not exported.
    [[maybe_unused]] const auto& d1 = x.getData(); // however, Data is reachable.

    /* reachability vs visibility.
     * Certain types are not visible but still reachable. This happens when an exported type provides an interface
     * which returns an unexported type.
     */
}