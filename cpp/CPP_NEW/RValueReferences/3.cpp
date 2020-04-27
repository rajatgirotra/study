/* Lets see another example of a simple function which has been overloaded for move sematics. */
#include <iostream>
using namespace std;
class X {
private:
    char* data;

public:
    X() {
        data = new char[100];
    }

    ~X() {
        if(data) {
           delete[] data;
           data = 0;
        }
     }

};

void foo(const X& ) {
   cout << "Classical Implementation" << endl;
}

void foo(X&& ) {
    cout << "Move semantics implementation" << endl;
}

int main() {
   X x;
   foo(x);

   foo(X());
}


