/*
Subtyping
Now suppose you want to create a type of ifstream object that not only opens a file but also keeps track of the name of the file. You can use composition and embed both an ifstream and a string into the new class:
*/

//: C14:FName1.cpp
// An fstream with a file name
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

class FName1 {
    string fileName;
    ifstream file;
    bool named;
public:
    FName1() : named(false) {}

    FName1(const string &fname)
            : fileName(fname), file(fname.c_str()) {
        assert(!fileName.empty());
        named = true;
    }

    string name() const { return fileName; }

    void name(const string &newName) {
        if (named) return; // Don't overwrite
        fileName = newName;
        named = true;
    }

    operator ifstream &() {
        cout << "operator ifstream&() called " << endl;
        return file;
    }
};

int main() {
    FName1 file("FName1.cpp");
    cout << file.name() << endl;
    // Error: close() not a member:
    //! file.close();
} ///:~

/*

There.s a problem here, however. An attempt is made to allow the use of the FName1 object anywhere an ifstream object is used by including an automatic type conversion operator from FName1 to an ifstream&. But in main, the line
    file.close();
will not compile because automatic type conversion happens only in function calls, not during member selection. So this approach won.t work.

A second approach is to add the definition of close( ) to FName1:
    void close() { file.close(); }
This will work if there are only a few functions you want to bring through from the ifstream class. In that case you.re only using part of the class, and composition is appropriate.
*/
