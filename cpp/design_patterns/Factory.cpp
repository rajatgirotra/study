/* The factory pattern encapsulates object creation 

When you discover that you need to add new types to a system, the most sensible first step is to use polymorphism to create a common interface to those new types. This separates the rest of the code in your system from the knowledge of the specific types that you are adding. New types can be added without disturbing existing code  or so it seems. At first it would appear that you need to change the code only in the place where you inherit a new type, but this is not quite true. You must still create an object of your new type, and at the point of creation you must specify the exact constructor to use. Thus, if the code that creates objects is distributed throughout your application, you have the same problem when adding new typesyou must still chase down all the points of your code where type matters. It is the creation of the type that matters here, rather than the use of the type (which is taken care of by polymorphism), but the effect is the same: adding a new type can cause problems.

The solution is to force the creation of objects to occur through a common factory rather than to allow the creational code to be spread throughout your system. If all the code in your program must go to this factory whenever it needs to create one of your objects, all you must do when you add a new object is modify the factory. This design is a variation of the pattern commonly known as Factory Method. Since every object-oriented program creates objects, and since its likely you will extend your program by adding new types, factories may be the most useful of all design patterns.

As an example, consider the commonly-used Shape example. One approach to implementing a factory is to define a static member function in the base class:

*/

#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
using namespace std;

class Circle;
class Square;

class Shape
{

public:
   virtual void draw() = 0;
   virtual void erase() = 0;

   virtual ~Shape()
   {
      cout<<"Shape d'tor executing"<<endl;
   }

   static Shape* createObject(const string& type);
};

class Circle : public Shape
{
   Circle()
   { };

   friend class Shape;

public:
   void draw()
   {
      cout<<"Circle::draw()"<<endl;
   }

   void erase()
   {
      cout<<"Circle::erase()"<<endl;
   }
};



class Square : public Shape
{
   Square()
   { };

   friend class Shape;

public:
   void draw()
   {
      cout<<"Square::draw()"<<endl;
   }

   void erase()
   {
      cout<<"Square::erase()"<<endl;
   }
};

Shape* Shape::createObject(const string& type)
{
   if(type == "Circle") return (new Circle());
   if(type == "Square") return (new Square());
}

string s1[] = {"Square", "Circle", "Circle", "Square" };

int main()
{
   vector<Shape*> objects;
   int i = 0;
   for(i = 0; i < sizeof(s1)/sizeof(s1[0]); ++i)
      objects.push_back(Shape::createObject(s1[i]));

   vector<Shape*>::iterator iter;

   for(iter = objects.begin(); iter != objects.end(); ++iter)
   {
      (*iter)->draw();
      (*iter)->erase();
   }
   return 0;
}
/*

There is another important implication of this designthe base class, Shape, must now know the details about every derived classa property that object-oriented designs try to avoid. For frameworks or any class library that should support extension, this can quickly become unwieldy, as the base class must be updated as soon as a new type is added to the hierarchy. Polymorphic factories, described in the next subsection, can be used to avoid this unfortunate circular dependency.

*/
