#include "turtle_impl.hpp"
#include <iostream>
using namespace std;
int main()
{
    Turtle* poT = new TurtleProd;
    poT->PenUp();
    poT->PenDown();
    poT->Forward(333);
    poT->Turn(90);
    poT->GoTo(3,5);
    auto x = poT->GetX();
    auto y = poT->GetY();
    cout <<  x << ", " << y << endl;

    return 0;
}
