/*
Please read 3.cpp first. Then note the size of the classes in this file.
*/

#include <iostream>
using namespace std;

class Base
{
private:
   int x;
public:
 virtual ~Base();

};

//class Derv : public Base
class Derv : virtual public Base
{
int y;
};

int main()
{
   cout<<"Size of Base: " << sizeof(Base)<<endl;
   cout<<"Size of Derv: " << sizeof(Derv)<<endl; // --> The derived class is given an additional field, which is a pointer to the Base class object.
    // so its size is: x + y + VPTR + pointer to Base = 4 * 4 = 16 bytes.
   return 0;
}

