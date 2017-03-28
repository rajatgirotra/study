//: C13:MallocClass.cpp
// Malloc with class objects
// What you'd have to do if not for "new"
#include "../require.h"
#include <cstdlib> // malloc() & free()
#include <cstring> // memset()
#include <iostream>
using namespace std;

class Obj {
   int i, j, k;
   enum { sz = 100 };
   char buf[sz];
   public:
   void initialize() { // Can't use constructor
      cout << "initializing Obj" << endl;
      i = j = k = 0;
      memset(buf, 0, sz);
   }
   void destroy() const { // Can't use destructor
      cout << "destroying Obj" << endl;
   }
};

int main() {
   Obj* obj = (Obj*)malloc(sizeof(Obj));
   require(obj != 0);
   obj->initialize();
   // ... sometime later:
   obj->destroy();
   free(obj);
} ///:~

/*

You can see the use of malloc( ) to create storage for the object in the line:

Obj* obj = (Obj*)malloc(sizeof(Obj));

Here, the user must determine the size of the object (one place for an error). malloc( ) returns a void* because it just produces a patch of memory, not an object. C++ doesn.t allow a void* to be assigned to any other pointer, so it must be cast.

Because malloc( ) may fail to find any memory (in which case it returns zero), you must check the returned pointer to make sure it was successful.

But the worst problem is this line:

Obj->initialize();

If users make it this far correctly, they must remember to initialize the object before it is used. Notice that a constructor was not used because the constructor cannot be called explicitly. it's called for you by the compiler when an object is created. The problem here is that the user now has the option to forget to perform the initialization before the object is used, thus reintroducing a major source of bugs.

There is a special syntax called placement new that allows you to call a constructor for a pre-allocated piece of memory.

 */
