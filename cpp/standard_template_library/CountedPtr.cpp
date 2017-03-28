#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

template <typename T>
class CountedPtr
{
private:
   T* ptr;
   long* count;

public:
   CountedPtr (T* arg = 0) : ptr(arg), count(new long(1))
   {
   };

   //copy c'tor
   CountedPtr(const  CountedPtr<T>& roPtr) : ptr(roPtr.ptr), count(roPtr.count)
   {
      ++*count;
   }

   //assignment
   CountedPtr& operator = (const CountedPtr<T>& roPtr)
   {
      if(--*count == 0)
         delete ptr;

      ptr = roPtr.ptr;
      count = roPtr.count;
      ++*count;
   }

   ~CountedPtr()
   {
      if(--*count == 0)
         delete ptr;
      ptr = 0;
   }

   T& operator* () const
   {
      return *ptr;
   }
  
   T& operator* ()
   {
      return *ptr;
   }

   T* operator -> () const
   {
      return ptr;
   }

   T* operator -> ()
   {
      return ptr;
   }
};

class Employee
{
private:
   string empName;
   long empID;

public:
   Employee(const string& m_name, const long& m_id) : empName(m_name), empID(m_id)
   {
   }

   void display()
   {
      cout<<"Name: "<<empName<<"    ID: "<<empID<<endl;
   }
};

int main()
{

   int i,j;
   Employee* o1 = new Employee("Rajat Girotra", 148);
   Employee* o2 = new Employee("Mark Dyne", 150);
   Employee* o3 = new Employee("Sanjesh Parmar", 154);
   Employee* o4 = new Employee("Emma Harris", 158);


   typedef CountedPtr<Employee> empCounted;

   vector<empCounted> vect;
   list<empCounted> lst;

   empCounted e1(o1);
   empCounted e2(o2);
   empCounted e3(o3);
   empCounted e4(o4);


   vect.push_back(e1);
   vect.push_back(e2);
   vect.push_back(e3);
   vect.push_back(e4);

   lst.push_back(e1);
   lst.push_back(e2);
   lst.push_back(e3);
   lst.push_back(e4);

   vector<empCounted>::iterator vectIter;
   list<empCounted>::iterator lstIter;

   for(vectIter = vect.begin(); vectIter != vect.end(); ++vectIter)
   {
      (**vectIter).display();
   }

   vectIter = vect.begin() + 2;
   vect.erase(vectIter);

   cout<<endl<<"After deletion"<<endl;

   cout<<"Vector: "<<endl;
   for(vectIter = vect.begin(); vectIter != vect.end(); ++vectIter)
   {
      (**vectIter).display();
   }

   cout<<"List: "<<endl;
   for(lstIter = lst.begin(); lstIter != lst.end(); ++lstIter)
   {
     (**lstIter).display();
   }

   return 0;
}

   
   


