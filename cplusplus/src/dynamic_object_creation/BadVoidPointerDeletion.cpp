/*
delete void* is probably a bug

It's worth making a point that if you call delete for a void*, it's almost certainly going to be a bug in your program unless the destination of that pointer is very simple; in particular, it should not have a destructor. Here's an example to show you what happens:

*/

    //: C13:BadVoidPointerDeletion.cpp
    // Deleting void pointers can cause memory leaks
    #include <iostream>
    using namespace std;

    class Object {
      void* data; // Some storage
      const int size;
      const char id;
    public:
      Object(int sz, char c) : size(sz), id(c) {
        data = new char[size];
        cout << "Constructing object " << id 
             << ", size = " << size << endl;
      }
      ~Object() { 
        cout << "Destructing object " << id << endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdelete-incomplete"
        delete []data; // OK, just releases storage,
#pragma GCC diagnostic pop
        // no destructor calls are necessary
      }
    };

    int main() {
      Object* a = new Object(40, 'a');
      delete a;
      void* b = new Object(40, 'b');
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdelete-incomplete"
      delete b;
#pragma GCC diagnostic pop
    } ///:~

/*

The class Object contains a void* that is initialized to "raw" data (it doesn"t point to objects that have destructors). In the Object destructor, delete is called for this void* with no ill effects, since the only thing we need to happen is for the storage to be released.

However, in main( ) you can see that it"s very necessary that delete know what type of object it"s working with. Here"s the output:

    Constructing object a, size = 40
    Destructing object a
    Constructing object b, size = 40

Because delete a knows that a points to an Object, the destructor is called and thus the storage allocated for data is released. However, if you manipulate an object through a void* as in the case of delete b, the only thing that happens is that the storage for the Object is released . but the destructor is not called so there is no release of the memory that data points to. When this program compiles, you probably won"t see any warning messages; the compiler assumes you know what you"re doing. So you get a very quiet memory leak.

If you have a memory leak in your program, search through all the delete statements and check the type of pointer being deleted. If it"s a void* then you"ve probably found one source of your memory leak (C++ provides ample other opportunities for memory leaks, however).

*/
