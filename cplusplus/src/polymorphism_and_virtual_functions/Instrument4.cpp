//: C15:Instrument4.cpp
// Extensibility in OOP
#include <iostream>
using namespace std;
enum Note { middleC, Csharp, Cflat }; // Etc.

class Instrument {
public:
  virtual void play(Note) const {
    cout << "Instrument::play" << endl;
  }
  virtual const char* what() const {
    return "Instrument";
  }
  // Assume this will modify the object:
  virtual void adjust(int) { cout<<"Instrument::adjust()"<<endl; }

  virtual ~Instrument() {}
};

class Wind : public Instrument {
public:
  void play(Note) const {
    cout << "Wind::play" << endl;
  }
  const char* what() const { return "Wind"; }
  void adjust(int) { cout<<"Wind::adjust()"<<endl; }
};

class Percussion : public Instrument {
public:
  void play(Note) const {
    cout << "Percussion::play" << endl;
  }
  const char* what() const { return "Percussion"; }
  void adjust(int) { cout<<"Percussion::adjust()"<<endl; }
};

class Stringed : public Instrument {
public:
  void play(Note) const {
    cout << "Stringed::play" << endl;
  }
  const char* what() const { return "Stringed"; }
  void adjust(int) { cout<<"Stringed::adjust()"<<endl; }
};

class Brass : public Wind {
public:
  void play(Note) const {
    cout << "Brass::play" << endl;
  }
  const char* what() const { return "Brass"; }
};

class Woodwind : public Wind {
public:
  void play(Note) const {
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

// Upcasting during array initialization:
Instrument* A[] = {
  new Wind,
  new Percussion,
  new Stringed,
  new Brass,
};

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

/*

You can see that another inheritance level has been added beneath Wind, but the virtual mechanism works correctly no matter how many levels there are. The adjust( ) function is not overridden for Brass and Woodwind. When this happens, the closest definition in the inheritance hierarchy is automatically used  the compiler guarantees theres always some definition for a virtual function, so youll never end up with a call that doesnt bind to a function body. (That would be disastrous.)

*/
