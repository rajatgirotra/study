#include <iostream>
using namespace std;

class A {
   static int i;
};

int main() {
   A obj;
   cout << sizeof(obj) << endl;
   return 0;
}
