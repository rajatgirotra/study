What are const RValues (const X&&)? and What good are they??
It turns out they are pointless- But you should still remember the binding rules below so you can avoid surprises in your code
and debug difficult to comprehend code.

The binding rule is that a const rvalue will prefer to bind to the const rvalue reference rather than to a const lvalue reference.
Let's see an example:

struct S{};

void f(S&);         # 1
void f(const S&);   # 2
void f(S&&);        # 3
void f(const S&&);  # 4

const S g();
S x;
const S cx;

f(s()); // argument is non-const rvalue, so binding preference will be #3, #4, #2
f(g()); // argument is const rvalue, so binding preference is #4, #2
f(x); // argument is lvalue, so binding preference is #1, #2
f(cx); // argument is const lvalue, so binding preference is #2

If you think: move semantics means the argument should be a non-const rvalue reference. because the argument has to be moved
from. So how can it be const? If you have a const rvalue reference, it means you are really not going to move anything.
So again what good is a const rvalue reference. Also consider the following example:

class Annotation {
   private:
       std::string mValue;
    public:
    explicit Annotation(const std::string text) : mValue(std::move(text)) {
    };
};

std::move(text) will return a "const std::string&&", so it cannot bind to std::string(std::string&&). This means
that it will bind to std::string(const std::string&); ie the copy c'tor will be called to initialize mValue.

One very limited use of "const X&&" is when you want to disable r-value references completely for your type. Example: for
std::reference_wrapper, the ref() and cref() functions are deleted for const r-value references. This ensures they are deleted
for both const and non-const rvalue references.

template <typename T>
void ref(const T&&) = delete;

template <typename T>
void cref(const T&&) = delete;
