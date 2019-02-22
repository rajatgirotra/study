RValue References - The single most difficult topic in C++11 to understand and apply.
Here we go:

LValue - An lvalue is an expression that refers to a memory location and allows you to take the address of that memory location
using the & (ampersand) operator.

RValue - An rvalue is an expression that is not an lvalue.

Eg:

 int x = 42; //42 is an rvalue, x is an lvalue.
 int a = x; // both a and x are lvalues.

 a * x = 30; //ERROR. a * x is an rvalue.


Rvalue references were introduced in C++0x11 to solve two problems:

1] Move semantics
2] Perfect forwarding

1] Move semantics - Let's say we have a user defined type X which holds a pointer to some data say m_resource. The assignment
   operator will look like
    X& operator = (const X& rhs) {
	// 1. Delete the resource pointed to by this.
        // 2. Clone m_resource pointed to by rhs.
        // 3. Update the m_resource pointer for this with the newly cloned pointer.
    }

    Now, in case the assignment operator is called like:
    X foobar();
    X x;
    x = foobar(); //i.e in case where the right hand side is an rvalue, we can just swap the m_resource pointers between this 
    and the temporary object returned by foobar(). Then when the temporary object goes out of scope after the assignment, the 
    m_resource originally pointed to by this gets deleted. This helps in drastic performance improvements as we are not cloning
    the resource anymore if the right hand side is an rvalue. So we provide an overload for the assignment operator for rvalue
    references.
   
   X& operator = (X&& rhs) {
      //swap m_resource between this and rhs.
      return *this;
   }

   The same applies to the copy c'tor and any other function which takes X as an argument.
   So if X is a user defined type, the X&& is called an rvalue reference to X.

Note that move is not only an optimization over copy, it has a semantic meaning also - transferring ownership.
When you move, you effectively xfer the ownership of the underlying resource. Think in your head about std::unique_ptr etc.
and you'll understand what i am trying to say.