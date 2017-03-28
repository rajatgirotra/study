#include <iostream>
#include <vector>

using namespace std;

class Base
{
public:
   Base(int i = 23) 
   {
      cout<<"Base c'tor "<<endl;
   }

   Base(const Base& roBase)
   {
      cout<<"Base copy c'tor "<<endl;
   }
   Base& operator = (const Base& roBase)
   {
      cout<<"Base assignment operator= "<<endl; 
   }

   ~Base()
   {
       cout <<"Base d'tor" << endl;
   }

private:

};

int main()
{
vector<Base> vectBasePtrs;

/* Whenever we use the resize function, the stl container created a temporary object and then uses it to to create objects using copy ctor.
 * These objects created using copy c'tor are stored in the container; and the temp object is destroyed.
*/
vectBasePtrs.resize(5); //calls the c'tor once & copy c'tor 5 times.

cout << "Exiting main" << endl;
return 0;
}

   
