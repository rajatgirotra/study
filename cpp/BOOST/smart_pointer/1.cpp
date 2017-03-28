/* boost::scoped_ptr<T> */
/* The boost scoped_ptr class is used to ensure deletion of a dynamically allocated object. The object pointed to is guaranteed to be deleted, either on destruction of the scped_ptr, or via an explicit call to the reset() function.

The difference between STL auto_ptr and scoped_ptr is that scoped_ptr does not transfer ownership. Also copy construction and assignment is not allowed.
It is a lightweight smart pointer; using it doesn't make your program larger or run slower. It only makes your code safer and more maintainable.

Synopsis

namespace boost {

  template<class T> class scoped_ptr : noncopyable {

   public:
     typedef T element_type;

     explicit scoped_ptr(T * p = 0); // never throws
     ~scoped_ptr(); // never throws

     void reset(T * p = 0); // never throws

     T & operator*() const; // never throws
     T * operator->() const; // never throws
     T * get() const; // never throws
     
     void swap(scoped_ptr & b); // never throws
  };

  template<class T> void swap(scoped_ptr<T> & a, scoped_ptr<T> & b); // never throws

}

The above synopsis is fairly straight forward.
scoped_ptr cannot be used in C++ Standard Library containers. Use shared_ptr if you need a smart pointer that can.

scoped_ptr cannot correctly hold a pointer to a dynamically allocated array. See scoped_array for that usage.

Because scoped_ptr::get returns a raw pointer, it is possible to do evil things to a scoped_ptr, and there are two things that you'll especially want to avoid. First, do not delete the stored pointer. It is deleted once again when the scoped_ptr is destroyed. Second, do not store the raw pointer in another scoped_ptr (or any smart pointer for that matter). Bad things happen when the pointer is deleted twice, once by each scoped_ptr. Simply put, minimize the use of get, unless you are dealing with legacy code that requires you to pass the raw pointer!

*/
#include <boost/scoped_ptr.hpp>
#include <iostream>

struct Shoe
{
 ~Shoe() 
  { 
     std::cout << "Buckle my shoe\n"; 
  } 
};

class MyClass
{
    boost::scoped_ptr<int> ptr;
  public:
    MyClass() : ptr(new int) { *ptr = 0; }
    int add_one() { return ++*ptr; }
};

int main()
{
    boost::scoped_ptr<Shoe> x(new Shoe);
    MyClass my_instance;
    std::cout << my_instance.add_one() << '\n';
    std::cout << my_instance.add_one() << '\n';
}
