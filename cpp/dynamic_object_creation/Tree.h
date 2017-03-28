#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
using namespace std;

class Tree
{
unsigned int height;

public:
   Tree(unsigned int p_height) : height(p_height)
   { };

   ~Tree() 
    { cout<<"Destructing Tree\n"<<endl; }

   friend std::ostream& operator << (std::ostream& os, const Tree* poTree)
   {
      os <<endl<<"Tree height is "<<poTree->height<<endl;
      return os;
   }
};

#endif 
