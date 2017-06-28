/*
Prefer alias declarations to typedef. The reason is 
1) ease of use and understanding and
2) alias types can be templatized.

Example 1: lets decalare a unique ptr of unordered map of string string
---------------------------------------------------------------------

typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;
vs
using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;

typedef void (*FP)(int, double);
vs
using FP = void (*)(int, double); // FP is a function pointer type.


Example 2
--------------------------------------------
// Create an std::list type with a custom allocator called MyAlloc
// old C++98 typedef approach

template <typename T>
struct MyAllocList {
    typedef typename std::list<T, MyAlloc<T>> type;
};

typedef MyAllocList<Widget>::type lw;  // client code

VS

template <typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;

MyAllocList<Widget> lw; // client code, How cool is that.


Example 3:
--------------------------------------------------
Let say you want to create the MyAllocList as part of a Widget template class

template <typename T>
class Widget {
    typename MyAllocList<T>::type list; // uncool :-( infact MyAllocList<T>::type is a dependant type
};

template <typename T>
class Widget {
    MyAllocList<T> list;  // cool, no typename, no ::type, infact MyAllocList is a non-dependant type
};
*/

/*
C++11 has <type_traits> which offers many type manipulating template classes: Eg remove_const
template <typename T>
struct {
   typedef some_magic<T>::type;  // This uses the old approach
}

C++14 has added "_t" counterparts based on alias templates. Very easy
template <typename T>
using remove_const_t = std::remove_const<T>::type;
*/
