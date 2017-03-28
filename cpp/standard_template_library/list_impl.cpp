#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;

void printLists (const list<int>& l1, const list<int>& l2)
{
  cout << "list1: ";
  copy (l1.begin(), l1.end(), ostream_iterator<int>(cout," "));

  cout << endl << "list2: ";
  copy (l2.begin(), l2.end(), ostream_iterator<int>(cout," "));
  cout << endl << endl;
}

int main()
{
  //create two empty lists
  list<int> list1, list2;

  //fill both lists with elements
  for (int i=0; i<6; ++i)
  {
    list1.push_back(i);
    list2.push_front(i);
  }

  printLists(list1, list2);

  //insert all elements of list1 before the first element with value 3 of list2
  list2.splice(find(list2.begin(), list2.end(), 3), list1);

  printLists(list1, list2);

  //move first element to the end
  list2.splice(list2.end(), // destination position
               list2, // source list
               list2.begin()); // source position

  printLists(list1, list2);

  //sort second list, assign to list1 and remove duplicates
  list2.sort();
  list1 = list2;
  list2.unique();
  
  printLists(list1, list2);
  
  //merge both sorted lists into the first list
  list1.merge(list2);
  printLists(list1, list2);

  /* Testing list deletion */
  cout<<"Testing list deletion"<<endl;
  int rolls[] = { 0,5,1,5,2,5,3,5,4,5,6,5,7,5};
  
  list<int> rollList(rolls, rolls+sizeof(rolls)/sizeof(rolls[0]));

  list<int>::iterator rollListIter;
  for(rollListIter = rollList.begin(); rollListIter != rollList.end();)
  {
      if(*rollListIter == 5) 
      { 
          rollListIter = rollList.erase(rollListIter);
          cout<<*rollListIter++<<endl;
      }
      else
      {
          cout<<*rollListIter<<endl;
          ++rollListIter;
      } 
  }
      
  return 0;
}
