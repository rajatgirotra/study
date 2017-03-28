Simple thing to remember about rvalue references

void foo(X& x);
void foo(X&& x);

X x;
X foobar();

foo(x); //calls foo(X&)
foo(foobar()); //calls foo(X&&)


