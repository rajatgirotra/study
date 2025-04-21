#include <iostream>

import Square; // import module “Square”

int main()
{
    Square x = toSquare(42);
    std::cout << x.getValue() << '\n';
}