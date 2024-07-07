//: C15:Instrument2.cpp
// Inheritance & upcasting
#include <iostream>
using namespace std;
enum Note { middleC, Csharp, Eflat }; // Etc.

class Instrument {
public:
 virtual void play(Note) const;
 virtual ~Instrument() {}
};

void Instrument::play(Note) const
{
   cout<<"Instrument::play"<<endl;
}

// Wind objects are Instruments
// because they have the same interface:
class Wind : public Instrument {
public:
  // Redefine interface function:
  void play(Note) const override {
    cout << "Wind::play" << endl;
  }
};

void tune(Instrument& i) {
  // ...
  i.play(middleC);
}

int main() {
  Wind flute;
  tune(flute); // Upcasting
} ///:~

