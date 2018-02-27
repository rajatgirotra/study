// Create a vector of 10 auto_ptr objects to employee class. & Study its behavior 

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
using namespace std;

class Employee
{
public:
   Employee()
   {
      cout<<"Employee c'tor running "<<endl;
   };

   virtual ~Employee()
   {
      cout<<"Employee d'tor running "<<endl;
   }
};

int main()
{
   typedef std::auto_ptr<Employee> autoPtrEmployee;
   typedef vector<autoPtrEmployee > autoPtrVector;
   int i;
   
   autoPtrEmployee poEmployee[10];
   autoPtrVector myVect;
   for(i = 0; i < 10; ++i)
   {
      poEmployee[i] = autoPtrEmployee(new Employee());
      myVect.push_back(poEmployee[i]);
   }
  
   return 0;
}
 

