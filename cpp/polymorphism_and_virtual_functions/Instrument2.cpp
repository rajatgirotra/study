//: C15:Instrument2.cpp
// Inheritance & upcasting
#include <iostream>
using namespace std;
enum note { middleC, Csharp, Eflat }; // Etc.

class Instrument {
public:
  void play(note) const {
    cout << "Instrument::play" << endl;
  }
};

// Wind objects are Instruments
// because they have the same interface:
class Wind : public Instrument {
public:
  // Redefine interface function:
  void play(note) const {
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

/*

The function tune( ) accepts (by reference) an Instrument, but also without complaint anything derived from Instrument. In main( ), you can see this happening as a Wind object is passed to tune( ), with no cast necessary. This is acceptable; the interface in Instrument must exist in Wind, because Wind is publicly inherited from Instrument. Upcasting from Wind to Instrument may narrow that interface, but never less than the full interface to Instrument.


The problem
The problem with Instrument2.cpp can be seen by running the program. The output is Instrument::play. This is clearly not the desired output, because you happen to know that the object is actually a Wind and not just an Instrument. The call should produce Wind::play. For that matter, any object of a class derived from Instrument should have its version of play( ) used, regardless of the situation.


Function call binding

Connecting a function call to a function body is called binding. When binding is performed before the program is run (by the compiler and linker), its called early binding. You may not have heard the term before because its never been an option with procedural languages: C compilers have only one kind of function call, and thats early binding.


The problem in the program above is caused by early binding because the compiler cannot know the correct function to call when it has only an Instrument address.


The solution is called late binding, which means the binding occurs at runtime, based on the type of the object. Late binding is also called dynamic binding or runtime binding. When a language implements late binding, there must be some mechanism to determine the type of the object at runtime and call the appropriate member function. In the case of a compiled language, the compiler still doesnt know the actual object type, but it inserts code that finds out and calls the correct function body. The late-binding mechanism varies from language to language, but you can imagine that some sort of type information must be installed in the objects. Youll see how this works later.


virtual functions
To cause late binding to occur for a particular function, C++ requires that you use the virtual keyword when declaring the function in the base class. Late binding occurs only with virtual functions, and only when youre using an address of the base class where those virtual functions exist, although they may also be defined in an earlier base class.


To create a member function as virtual, you simply precede the declaration of the function with the keyword virtual. Only the declaration needs the virtual keyword, not the definition. If a function is declared as virtual in the base class, it is virtual in all the derived classes. The redefinition of a virtual function in a derived class is usually called overriding.


Notice that you are only required to declare a function virtual in the base class. All derived-class functions that match the signature of the base-class declaration will be called using the virtual mechanism. You can use the virtual keyword in the derived-class declarations (it does no harm to do so), but it is redundant and can be confusing. 


*/


