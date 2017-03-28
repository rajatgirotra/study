/*
   An abstract factory pattern is also similar to the other Factory patterns except that here you have multiple factory methods.
   Each factory method can be used to create objects in a particluar class hierarchy.
   This is illustrated below:
 */

//: C09:AbstractFactory.cpp
// A gaming environment
#include <iostream>
using namespace std;
class Obstacle {
    public:
        virtual void action() = 0;
}; //base class of one class hierarchy.

class Player {
    public:
        virtual void interactWith(Obstacle*) = 0;
}; //base class of second class hierarchy.

class Kitty: public Player {
    virtual void interactWith(Obstacle* ob) {
        cout << "Kitty has encountered a ";
        ob->action();
    }
}; //second class hierarchy

class KungFuGuy: public Player {
    virtual void interactWith(Obstacle* ob) {
        cout << "KungFuGuy now battles against a ";
        ob->action();
    }
}; //second class hierarchy

class Puzzle: public Obstacle {
    public:
        void action() { cout << "Puzzle\n"; }
};  //first call hierarchy.

class NastyWeapon: public Obstacle {
    public:
        void action() { cout << "NastyWeapon\n"; }
};  //first call hierarchy.
 
// The abstract factory:
class GameElementFactory {
    public:
        virtual Player* makePlayer() = 0;
        virtual Obstacle* makeObstacle() = 0;
};  //The abstract factory base class.

// Concrete factories:
class KittiesAndPuzzles :
    public GameElementFactory {
        public:
            virtual Player* makePlayer() {
                return new Kitty;
            }
            virtual Obstacle* makeObstacle() {
                return new Puzzle;
            }
    }; // The concrete class factory.
class KillAndDismember :
    public GameElementFactory {
        public:
            virtual Player* makePlayer() {
                return new KungFuGuy;
            }
            virtual Obstacle* makeObstacle() {
                return new NastyWeapon;
            }
    };
class GameEnvironment {
    GameElementFactory* gef;
    Player* p;
    Obstacle* ob;
    public:
    GameEnvironment(GameElementFactory* factory) :
        gef(factory), p(factory->makePlayer()),
        ob(factory->makeObstacle()) {}
    void play() {
        p->interactWith(ob);
    }
    ~GameEnvironment() {
        delete p;
        delete ob;
        delete gef;
    }
};
int main() {
    GameEnvironment
        g1(new KittiesAndPuzzles),
            g2(new KillAndDismember);
    g1.play();
    g2.play();
} ///:~
