/*

Here is the syntax used for a pure virtual declaration:

    virtual void f() = 0;

By doing this, you tell the compiler to reserve a slot for a function in the VTABLE, but not to put an address in that particular slot. Even if only one function in a class is declared as pure virtual, the VTABLE is incomplete.

If the VTABLE for a class is incomplete, what is the compiler supposed to do when someone tries to make an object of that class? It cannot safely create an object of an abstract class, so you get an error message from the compiler. Thus, the compiler guarantees the purity of the abstract class. By making a class abstract, you ensure that the client programmer cannot misuse it.

Here's Instrument4.cpp modified to use pure virtual functions. Because the class has nothing but pure virtual functions, we call it a pure abstract class:
*/

    //: C15:Instrument5.cpp
    // Pure abstract base classes
    #include <iostream>
    using namespace std;
    enum note { middleC, Csharp, Cflat }; // Etc.

    class Instrument {
    public:
      // Pure virtual functions:
      virtual void play(note) const = 0;
      virtual const char* what() const = 0;
      // Assume this will modify the object:
      virtual void adjust(int) = 0;
    };
    // Rest of the file is the same ...

    class Wind : public Instrument {
    public:
      void play(note) const {
        cout << "Wind::play" << endl;
      }
      const char* what() const { return "Wind"; }
      void adjust(int) {}
    };

    class Percussion : public Instrument {
    public:
      void play(note) const {
        cout << "Percussion::play" << endl;
      }
      const char* what() const { return "Percussion"; }
      void adjust(int) {}
    };

    class Stringed : public Instrument {
    public:
      void play(note) const {
        cout << "Stringed::play" << endl;
      }
      const char* what() const { return "Stringed"; }
      void adjust(int) {}
    };

    class Brass : public Wind {
    public:
      void play(note) const {
        cout << "Brass::play" << endl;
      }
      const char* what() const { return "Brass"; }
    };

    class Woodwind : public Wind {
    public:
      void play(note) const {
        cout << "Woodwind::play" << endl;
      }
      const char* what() const { return "Woodwind"; }
    };

    // Identical function from before:
    void tune(Instrument& i) {
      // ...
      i.play(middleC);
    }

    // New function:
    void f(Instrument& i) { i.adjust(1); }

    int main() {
      Wind flute;
      Percussion drum;
      Stringed violin;
      Brass flugelhorn;
      Woodwind recorder;
      tune(flute);
      tune(drum);
      tune(violin);
      tune(flugelhorn);
      tune(recorder);
      f(flugelhorn);
    } ///:~

