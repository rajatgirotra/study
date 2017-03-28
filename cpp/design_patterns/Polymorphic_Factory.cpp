#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
using namespace std;

class Shape
{
   public:
      virtual void draw() = 0;
      virtual void erase() = 0;

      virtual ~Shape() {}
};

class ShapeFactory
{
   private:
      static map<string, ShapeFactory*> factory;
      virtual Shape* create() = 0;

   public:
      virtual ~ShapeFactory() {}

      class BadExceptionType : public logic_error
      {
         public:
         BadExceptionType(const string& id) : logic_error("Cannot Create Type" + id)
         { };
      };

      friend class ShapeFactoryInitializer;
      static Shape* createObject(const string& id) throw (BadExceptionType);
};

map<string, ShapeFactory*> ShapeFactory::factory;

Shape* ShapeFactory::createObject(const string& id) throw (BadExceptionType)
{
   if(factory.find(id) != factory.end())
      return factory[id]->create();

   else
      throw BadExceptionType(id);
}

class Circle : public Shape
{
   Circle()
   { };
public:
   friend class ShapeFactoryInitializer;
   class Factory;
   friend class Factory;
   class Factory : public ShapeFactory
   {
      public:
         Shape* create() { return new Circle; };
         friend class ShapeFactoryInitializer;
      virtual ~Factory() {};
   };

   void draw()
   {
      cout<<"Circle::draw()"<<endl;
   }

   void erase()
   {
      cout<<"Circle::erase()"<<endl;
   }

   virtual ~Circle()
   {
      cout<<"Circle::~Circle()"<<endl;
   }
};

class ShapeFactoryInitializer 
{
   static ShapeFactoryInitializer si;
   ShapeFactoryInitializer() 
   {
      ShapeFactory::factory["Circle"]= new Circle::Factory;
   }
   ~ShapeFactoryInitializer()
   {
      map<string, ShapeFactory*>::iterator it =
         ShapeFactory::factory.begin();
      while(it != ShapeFactory::factory.end())
         delete it++->second;
   }
};

ShapeFactoryInitializer ShapeFactoryInitializer::si;


int main()
{
   vector<Shape*> v;
   string s1[] = { "Circle", "Circle" };
   int i= 0;
   try
   {
      for(i = 0; i < sizeof(s1)/sizeof(s1[0]); ++i)
         v.push_back(ShapeFactory::createObject(s1[i]));
   }catch(ShapeFactory::BadExceptionType e)
   {
      cout<<"Exception Caught "<<e.what()<<endl;
   }

   for(i = 0; i < v.size(); ++i)
   {
      v[i]->draw();
      v[i]->erase();
   }

   return 0;
}
