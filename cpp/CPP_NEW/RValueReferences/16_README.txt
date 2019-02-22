Returning by std::move() or std::forward() and N(RVO).
======================================================

Let's understand first what is N(RVO). Very simple. RVO states that if a function returns by value and define a local variable
(named or un-named) of that type in your function and you also return that variable by value, then

1) The compiler must do copy-elision and directly create that object into the return location of the function
2) If the compiler cannot perform copy-elision, then it must return that variable as an rvalue. ie return type should be
implicitly: std::move(variable).
3) Function arguments are not eligible for N(RVO).

Example:

Widget foo() {
    Widget w;
    return w; // returning a local variable by value. compiler does copy-elision
}

Now if you have a function which returns by value and take an rvalue reference or universal reference as argument,
and it returns that argument from the function; then
1) It will not be eligible for RVO
2) You must use std::move()[for rvalue reference] and std::forward()[for universal reference]; as it will be more efficient.

Example:
========

Matrix operator + (const Matrix& lhs, Matrix&& rhs) {
    rhs.value += lhs.value;
    return std::move(rhs); // is more efficient.
}

template <typename T>
Fraction reduce(T&& frac) {
    frac.reduce();
    return std::forward<T>(frac);
}

CAVEAT
======
NEVER NEVER NEVER DO THIS..

HashMap getMap() {
    HashMap hm;
    return std::move(hm); // you just acted smart but you ended up being a fool. You disabled RVO.
}

// But you say.. RVO is a compiler optimization. if the compiler doesnt apply it, atleast my version will do a move and avoid
a copy??
Answer
1) First, most compiler will apply it anyway.
2) If they dont, just because the function code is complex and has too many code paths and the compiler cannot elide a copy,
the return type will automatically be an rvalue ie std::move(hm) will be implicit. You should just say "return hm";
THAT's IT.