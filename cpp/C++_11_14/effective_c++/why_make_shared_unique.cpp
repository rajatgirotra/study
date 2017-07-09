/* Very simple. Three reasons.
Reason 1 Exception safety.
--------------------------
void foo(std::shared_ptr<A> a, int priority);

int getPriority();
{
    foo(std::shared_ptr<A>(new A()), getPriority()); // this can cause a leak if "new A()" is called followed by getPriority() which throws an exception.
}
General rule of thumb
a) Either use std::make_shared<A>() or always use a named shared_ptr
{
    std::shared_ptr<A> spA(new A());
    foo(spA, getPriority);
}
OR
b) {
       foo(std::make_shared<A>(), getPriority());
}

Reason 2 Less typing
--------------------
auto spA(std::make_shared<A>()); // A is used once. vs
std::shared_ptr<A> spA (new A()); // A is used twice here.

Reason 3 More effecient
----------------------
std::shared_ptr<A> spA (new A());  --> needs two memory allocations, one for shared_ptr control block and one for resource A

auto spA(std::make_shared<A>()); --> needs one resource allocation, combined for both control block and for resource A.




Downside
--------
1) Cannot use custom deleters
2) Cannot delete the control block even if the no shared_ptr exists. This is because even if one weak_ptr exists, then the control block cannot be destroyed.

3) Also
auto spv = std::make_shared<std::vector<int>>(10, 20); // which vector ctor is called. One to initialize the vector with values 10 and 20 or the one to allocate 10 ints all with value 20. Remember that the make_shared/unique functions always use parenthesis to pass the arguments to the c'tor. So if you want your object to be initialized using an initializer_list, you will need to use new explicitly. The other reason why this is that the make function requires to perfectly forward its arguments, whereas the standard says that brace initializers cannot be perfectly forwarded. (they are always passed as const references). So make_ functions anyway cannot use brace initialization

