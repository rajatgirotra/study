//: C13:NewHandler.cpp
// Changing the new-handler
#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;


void out_of_memory()
{
   cerr << "memory exhausted!" << endl;
   exit(1);
}

int main() {
   set_new_handler(out_of_memory);
   while(1) {
     cout << "Allocating 1000000000 integers" << endl;
      new int[1000000000]; // Exhausts memory
   }
} ///:~

