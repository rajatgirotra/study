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

void foo(const std::auto_ptr<Employee>& autoEmployee)
//void foo(std::auto_ptr<Employee> autoEmployee)
{
}

int main()
{
   std::auto_ptr<Employee> emp(new Employee);
   foo(emp);
   cout<<"After call to foo()"<<endl;
   return 0;
}
 

