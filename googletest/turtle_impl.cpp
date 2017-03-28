#include "turtle_impl.hpp"
#include <iostream>
using namespace std;

void TurtleProd::PenUp()
{
    cout << "TurtleProd::PenUp()" << endl;
}

void TurtleProd::PenDown()
{
    cout << "TurtleProd::PenDown()" << endl;
}

void TurtleProd::Forward(int distance)
{
    cout << "TurtleProd::Forward() " << distance << endl;
}

void TurtleProd::Turn(int degrees)
{
    cout << "TurtleProd::Turn() " << degrees << endl;
}

void TurtleProd::GoTo(int x, int y)
{
    cout << "TurtleProd::GoTo() " << x << ", " << y  << endl;
}

int TurtleProd::GetX() const
{
    cout << "TurtleProd::GetX()"  << endl;
    return 100;
}

int TurtleProd::GetY() const
{
    cout << "TurtleProd::GetY()"  << endl;
    return -100;
}
