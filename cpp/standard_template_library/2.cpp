/* Create a person class, with firstname, lastname, and phone numbers. Store them in a set container; and perform operations on them; try to use lower_bound(), upper_bound() and other such member functions */

#include <iostream>
#include <string>
#include <set>
using namespace std;

class Person
{

private:
   string firstname;
   string lastname;
   unsigned long phoneNumber;

public:
   
   Person() : firstname(" "), lastname(" "), phoneNumber(0)
   { };

   Person(string p_fname, string p_lname, unsigned long p_no) : firstname(p_fname), lastname(p_lname), phoneNumber(p_no)
   { };

   void display() const
   {
      cout<<"FirstName = "<<this->firstname<<"   LastName = "<<this->lastname<<"   PhoneNumber = "<<this->phoneNumber<<endl;
   }

  //friend bool operator < (const Person&, const Person&);
  bool operator < (const Person&) const;

};
#if 1
bool Person::operator < (const Person& p1) const
{
   if(lastname == p1.lastname)
      return (firstname < p1.firstname);
   else
      return (lastname < p1.lastname);
}
#endif

#if 0
bool operator < (const Person& roPerson_1, const Person& roPerson_2)
{
   if(roPerson_1.lastname == roPerson_2.lastname)
      return (roPerson_1.firstname < roPerson_2.firstname);
   else
      return (roPerson_1.lastname < roPerson_2.lastname);
}
#endif

int main()
{
Person pers1("Rajat ", "Girotra", 99100046);
Person pers2("Vidhu ", "Girotra", 98101414);
Person pers3("Sudesh", "Ahuja  ", 11254995); 
Person pers4("Shweta", "Sethi  ", 19191991); 
Person pers5("Ankit ", "Bhutani", 98116407); 

set<Person, less<Person> >personSet;
set<Person, less<Person> >::iterator iter;

personSet.insert(pers1);
personSet.insert(pers2);
personSet.insert(pers3);
personSet.insert(pers4);
personSet.insert(pers5);

for (iter = personSet.begin(); iter != personSet.end(); ++iter)
(*iter).display();

return 0;
}

