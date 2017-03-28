#include <iostream>
#include <string>
using namespace std;

 unsigned long long* poULL;
void foo()
{
   static char* whole;
   if(whole)
      cout<<"whole is NOT NULL"<<endl;
   else
      cout<<"whole is NULL"<<endl;
   
   return;
}

int main()
{
   foo();

   if(poULL)
      cout<<"poULL is NOT NULL"<<endl;
   else
      cout<<"poULL is NULL"<<endl;
   return 0;
} 
