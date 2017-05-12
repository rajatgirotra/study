#include <iostream>
using namespace std;
struct mytype
{
    enum struct ACCESSORIES
    {
        GLARES,
        WATCH,
        BANGLES
    };
};

void foo(const mytype::ACCESSORIES& a)
{
    if (a == mytype::ACCESSORIES::WATCH)
       cout << "Watch" << endl;
}

int main() {
    enum struct Color : char
    {
        RED,
        PINK,
        ORANGE
    };

    enum Fruit : char
    {
    BANANA,
    ORANGE
    };

    Color c = Color::PINK;

    mytype::ACCESSORIES a =  mytype::ACCESSORIES::BANGLES;
    foo(a);
    return 0;
}
/*
Because older c++e enums were not strongly scoped: you could say

class MyType
{
    enum Color
	  {
	     ORANGE, PINK
		 };
};

int main()
{
    cout << Mytype::ORANGE << endl;
	}
*/
