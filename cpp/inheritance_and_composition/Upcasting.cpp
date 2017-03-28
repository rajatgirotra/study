//: C14:Instrument.cpp
// Inheritance & upcasting
enum note { middleC, Csharp, Cflat }; // Etc.

class Instrument {
public:
  void play(note) const {}
};

// Wind objects are Instruments
// because they have the same interface:
class Wind : public Instrument {};

void tune(Instrument& i) {
  // ...
  i.play(middleC);
}

int main() {
  Wind flute;
  tune(flute); // Upcasting
} ///:~

/*

Whats interesting in this example is the tune( ) function, which accepts an Instrument reference. However, in main( ) the tune( ) function is called by handing it a reference to a Wind object. Given that C++ is very particular about type checking, it seems strange that a function that accepts one type will readily accept another type, until you realize that a Wind object is also an Instrument object, and theres no function that tune( ) could call for an Instrument that isnt also in Wind (this is what inheritance guarantees). Inside tune( ), the code works for Instrument and anything derived from Instrument, and the act of converting a Wind reference or pointer into an Instrument reference or pointer is called upcasting.

*/

