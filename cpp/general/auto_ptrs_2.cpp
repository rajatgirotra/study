//util/autoptr2.cpp
#include <iostream>
#include <memory>
using namespace std;
/* define output operator for auto_ptr
 * - print object value or NULL
 */
  template <class T>
ostream& operator<< (ostream& strm, const auto_ptr<T>& p)
{
  //does p own an object ?
  if (p.get() == NULL) {
    strm << "NULL"; //NO: print NULL
  }
  else {
    strm << *p; //YES: print the object
  }
  return strm;
}



int main()
{
  const auto_ptr<int> p(new int(42));
  const auto_ptr<int> q(new int(0));
  const auto_ptr<int> r;
  cout << "after initialization:" << endl;
  cout << " p: " << p << endl;
  cout << " q: " << q << endl;
  cout << " r: " << r << endl;
  *q = *p;
  // *r = *p; //ERROR: undefined behavior
  *p = -77;
  cout << "after assigning values:" << endl;
  cout << " p: " << p << endl;
  cout << " q: " << q << endl;
  cout << " r: " << r << endl;
  // q = p; //ERROR at compile time
  //r = p; //ERROR at compile time
}

/*


Here, the output of the program is as follows:

after initialization:
p: 42
q: 0
r: NULL
after assigning values:
p: -77
q: 42
r: NULL

This example defines an output operator for auto_ptrs. To do this, it passes an auto_ptr as a constant reference. According to the discussion on page 43, you should usually not pass an auto_ptr in any form. This function is an exception to this rule. Note that the assignment

 *r = *p;

 is an error. It dereferences an auto_ptr that refers to no object. According to the standard, this results in undefined behavior; for example, a crash. As you can see, you can manipulate the objects to which constant auto_ptrs refer, but you can't change which objects they own. Even if r was nonconstant, the last statement would not be possible because it would change the constant p.

 */
