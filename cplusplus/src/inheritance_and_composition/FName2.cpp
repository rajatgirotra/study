/*
But what if you want everything in the class to come through? This is called subtyping because you.re making a new type from an existing type, and you want your new type to have exactly the same interface as the existing type (plus any other member functions you want to add), so you can use it everywhere you.d use the existing type. This is where inheritance is essential.
You can see that subtyping solves the problem in the preceding example perfectly:
*/

    //: C14:FName2.cpp
    // Subtyping solves the problem
    #include <iostream>
    #include <fstream>
    #include <string>
    using namespace std;

    class FName2 : public ifstream {
      string fileName;
      bool named;
    public:
      FName2() : named(false) {}
      FName2(const string& fname)
        : ifstream(fname.c_str()), fileName(fname) {
        named = true;
      }
      string name() const { return fileName; }
      void name(const string& newName) {
        if(named) return; // Don't overwrite
        fileName = newName;
        named = true;
      }
    };

    int main() {
      FName2 file("FName2.cpp");
      cout << "name: " << file.name() << endl;
      string s;
      getline(file, s); // These work too!
      file.seekg(-200, ios::end);
      file.close();
    } ///:~

/*
Now any member function available for an ifstream object is available for an FName2 object.
you can also see that non-member functions like getline() that expect an ifstream can also work with an FName1. That's because an FName2 is a type of ifstream; it doesn't simply contain one.
*/
