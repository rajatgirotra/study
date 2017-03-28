/* Map container demonstration */
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
   typedef map<string, float> Map;
   Map myMap;

   myMap["VAT"]  = 0.12;
   myMap["Pi"]   = 3.14;
   myMap["e"]    = 2.68;
   myMap["Null"] = 0;

   Map::iterator iter = myMap.begin();
   while(iter != myMap.end())
   {
      cout<<"Key   = "<<(*iter).first<<endl;
      cout<<"Value = "<<iter->second<<endl;
      cout<<endl; 
      ++iter;
   }
 
   return 0;
}
   
