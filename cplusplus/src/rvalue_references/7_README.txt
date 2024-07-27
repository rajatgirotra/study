Simple thing to remember about rvalue references

void foo(X& x);
void foo(X&& x);

X x;
X getX();

foo(x); //calls foo(X&)
foo(getX()); //calls foo(X&&)


