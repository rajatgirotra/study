/*

   Functions that don.t automatically inherit

   Not all functions are automatically inherited from the base class into the derived class. Constructors and destructors deal with the creation and destruction of an object, and they can know what to do with the aspects of the object only for their particular class, so all the constructors and destructors in the hierarchy below them must be called. Thus, constructors and destructors don.t inherit and must be created specially for each derived class.

   In addition, the operator= doesn.t inherit because it performs a constructor-like activity. That is, just because you know how to assign all the members of an object on the left-hand side of the = from an object on the right-hand side doesn.t mean that assignment will still have the same meaning after inheritance.

   In lieu of inheritance, these functions are synthesized by the compiler if you don.t create them yourself. (With constructors, you can.t create any constructors in order for the compiler to synthesize the default constructor and the copy-constructor.) This was briefly described in Chapter 6. The synthesized constructors use memberwise initialization and the synthesized operator= uses memberwise assignment. Here.s an example of the functions that are synthesized by the compiler:

 */

//: C14:SynthesizedFunctions.cpp
// Functions that are synthesized by the compiler
#include <iostream>
using namespace std;

class GameBoard {
  public:
    GameBoard() { cout << "GameBoard()\n"; }
    GameBoard(const GameBoard&) { 
      cout << "GameBoard(const GameBoard&)\n"; 
    }
    GameBoard& operator=(const GameBoard&) {
      cout << "GameBoard::operator=()\n";
      return *this;
    }
    ~GameBoard() { cout << "~GameBoard()\n"; }
};

class Game {
  GameBoard gb; // Composition
  public:
  // Default GameBoard constructor called:
  Game() { cout << "Game()\n"; }
  // You must explicitly call the GameBoard
  // copy-constructor or the default constructor
  // is automatically called instead:
  Game(const Game& g) : gb(g.gb) { 
    cout << "Game(const Game&)\n"; 
  }
  Game(int) { cout << "Game(int)\n"; }
  Game& operator=(const Game& g) {
    // You must explicitly call the GameBoard
    // assignment operator or no assignment at 
    // all happens for gb!
    gb = g.gb;
    cout << "Game::operator=()\n";
    return *this;
  }
  class Other {}; // Nested class
  // Automatic type conversion:
  operator Other() const {
    cout << "Game::operator Other()\n";
    return Other();
  }
  ~Game() { cout << "~Game()\n"; }
};

class Chess : public Game {};

void f(Game::Other) {}

class Checkers : public Game {
  public:
    // Default base-class constructor called:
    Checkers() { cout << "Checkers()\n"; }
    // You must explicitly call the base-class
    // copy constructor or the default constructor
    // will be automatically called instead:
    Checkers(const Checkers& c) : Game(c) {
      cout << "Checkers(const Checkers& c)\n";
    }
    Checkers& operator=(const Checkers& c) {
      // You must explicitly call the base-class
      // version of operator=() or no base-class
      // assignment will happen:
      Game::operator=(c);
      cout << "Checkers::operator=()\n";
      return *this;
    }
};

int main() {
  Chess d1;  // Default constructor
  Chess d2(d1); // Copy-constructor
  //!! Chess d3(1); // Error: no int constructor
  d1 = d2; // Operator= synthesized
  f(d1); // Type-conversion IS inherited
  Game::Other go;
  //!  d1 = go; // Operator= not synthesized 
  // for differing types
  cout<<endl<<endl;
  Checkers c1, c2(c1);
  c1 = c2;
} ///:~

/*

   The constructors and the operator= for GameBoard and Game announce themselves so you can see when they.re used by the compiler. In addition, the operator Other( ) performs automatic type conversion from a Game object to an object of the nested class Other. The class Chess simply inherits from Game and creates no functions (to see how the compiler responds). The function f( ) takes an Other object to test the automatic type conversion function.

   In main( ), the synthesized default constructor and copy-constructor for the derived class Chess are called. The Game versions of these constructors are called as part of the constructor-call hierarchy. Even though it looks like inheritance, new constructors are actually synthesized by the compiler. As you might expect, no constructors with arguments are automatically created because that.s too much for the compiler to intuit.

   The operator= is also synthesized as a new function in Chess using memberwise assignment (thus, the base-class version is called) because that function was not explicitly written in the new class. And of course the destructor was automatically synthesized by the compiler.

   Because of all these rules about rewriting functions that handle object creation, it may seem a little strange at first that the automatic type conversion operator is inherited. But it.s not too unreasonable . if there are enough pieces in Game to make an Other object, those pieces are still there in anything derived from Game and the type conversion operator is still valid (even though you may in fact want to redefine it).

   operator= is synthesized only for assigning objects of the same type. If you want to assign one type to another you must always write that operator= yourself.

   If you look more closely at Game, you.ll see that the copy-constructor and assignment operators have explicit calls to the member object copy-constructor and assignment operator. You will normally want to do this because otherwise, in the case of the copy-constructor, the default member object constructor will be used instead, and in the case of the assignment operator, no assignment at all will be done for the member objects!

   Lastly, look at Checkers, which explicitly writes out the default constructor, copy-constructor, and assignment operators. In the case of the default constructor, the default base-class constructor is automatically called, and that.s typically what you want. But, and this is an important point, as soon as you decide to write your own copy-constructor and assignment operator, the compiler assumes that you know what you.re doing and does not automatically call the base-class versions, as it does in the synthesized functions. If you want the base class versions called (and you typically do) then you must explicitly call them yourself. In the Checkers copy-constructor, this call appears in the constructor initializer list:

   Checkers(const Checkers& c) : Game(c) {

   In the Checkers assignment operator, the base class call is the first line in the function body:

   Game::operator=(c);

   These calls should be part of the canonical form that you use whenever you inherit a class.

 */
