/*

The State pattern produces an object that appears to change its class, and is useful when you discover that you have conditional code in most or all functions. Like Proxy, State is created by having a front-end object that uses a back-end implementation object to fulfill its duties. However, the State pattern switches from one implementation to another during the lifetime of the front-end object, in order to produce different behavior for the same function call(s). Its a way to improve the implementation of your code when you seem to be doing a lot of testing inside each of your functions before deciding what to do for that function. 

*/

#include <iostream>
using namespace std;

class Creature
{
private:

   class State
   {
     public:
      virtual void response() = 0;
   };
   
   class Frog : public State
   {
     public:
      void response()
      {
         cout<<"Yes i am a frog... Ribbet..!!"<<endl;
      }
   };

   class Prince : public State
   {
     public:
      void response()
      { 
         cout<<"Yes I am the handsome prince..!!"<<endl;
      }
   };

   State* poState;

public:
    Creature() : poState(new Frog())
    { };
  
    ~Creature()
    {
        if(poState)
         delete poState;
    }

    void greet()
    { 
        poState->response();
    }
 
    void kiss()
    {
       delete poState;
       poState = 0;
       poState = new Prince();
    };
};

int main()
{
Creature objCreature;
objCreature.greet();
objCreature.kiss(); 
objCreature.greet();
return 0;
}
