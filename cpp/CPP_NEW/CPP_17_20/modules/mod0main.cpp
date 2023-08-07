#include <iostream>

import Square;

int main()
{
    Square x = toSquare(42);
    std::cout << x.getValue() << '\n';
}