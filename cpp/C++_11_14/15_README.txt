The next big question is whether an rvalue reference is an lvalue or rvalue. For example,
if you have a type X with move semantics, and a function

void foo(X&& x) {
   X anotherX = x;  // ----> A
}

Then, does the line A call the move copy c'tor or classical copy c'tor.
The answer is: Things that are declared as rvalue references can be lvalues or rvalues. 
If the rvalue reference has a name, then it is an lvalue. If the rvalue reference does not have a name, 
then it is an rvalue.

If we allow move sematics to be applied to something that has a name, then the thing which we moved
is still accessible in the subsequent lines of code. I.e. the resource pointed to by anotherX will still be accessible
via x(ie. it is still in scope!!). However, in case an rvalue reference does not have a name, then it will get destroyed immediately making
sure that the resource gets deleted.

Eg: in

X&& goo();
X x = goo(); //here rvalue reference does not have a name, so move semantics is called.

Next I want you to write a Base and Derived class which overloads move semantics and demonstrate how
the c'tor heirarchy is called.


