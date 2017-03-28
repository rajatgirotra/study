/*

A Command is a function object in its purest sense: a function thats an object. By wrapping a function in an object, you can pass it to other functions or objects as a parameter, to tell them to perform this particular operation in the process of fulfilling your request. You could say that a Command is a Messenger that carries behavior.

*/


#include <iostream>
#include <vector>
using namespace std;

class Command
{
public:

   virtual void execute() = 0;
};

class Hello : public Command
{
public:
   void execute()
   {
      cout<<"Hello";
   }
};

class World : public Command
{
public:
   void execute()
   {
      cout<<" World.!! ";
   }
};

class IAm : public Command
{
public:
   void execute()
   {
      cout<<" I am the command pattern"<<endl;
   }
};

class Macro
{
private:

vector<Command*> poCommands;

public:

   void add(Command* poCommand)
   {
      poCommands.push_back(poCommand);
   }


   void run()
   {
      vector<Command*>::iterator it = poCommands.begin();
      while(it != poCommands.end())
      {
         (*it++)->execute();
      }
   }
};

int main()
{
Macro objMacro;
objMacro.add(new Hello());
objMacro.add(new World());
objMacro.add(new IAm());

objMacro.run();
return 0;
}

/*

The primary point of Command is to allow you to hand a desired action to a function or object. In the above example, this provides a way to queue a set of actions to be performed collectively. Here, you can dynamically create new behavior, something you can normally only do by writing new code but in the above example could be done by interpreting a script (see the Interpreter pattern if what you need to do gets very complex).

GoF says that Commands are an object-oriented replacement for callbacks.[141] However, we think that the word back is an essential part of the concept of callbacksa callback reaches back to the creator of the callback. On the other hand, with a Command object you typically just create it and hand it to some function or object, and you are not otherwise connected over time to the Command object.

A common example of Command is the implementation of undo functionality in an application. Each time the user performs an operation, the corresponding undo Command object is placed into a queue. Each Command object that is executed backs up the state of the program by one step.

Encapsulate a request as an object
thereby allowing clients to be parameterized with different requests, queue or log requests and support undoable operations

Also known as Action, Transaction

Allows issuing of requests on objects without knowing anything about operation being requested or the receiver of request
*/
