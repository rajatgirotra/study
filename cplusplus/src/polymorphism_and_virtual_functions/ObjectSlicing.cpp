/*

There is a distinct difference between passing the addresses of objects and passing objects by value when using polymorphism. All the examples you.ve seen here, and virtually all the examples you should see, pass addresses and not values. This is because addresses all have the same size[58], so passing the address of an object of a derived type (which is usually a bigger object) is the same as passing the address of an object of the base type (which is usually a smaller object). As explained before, this is the goal when using polymorphism . code that manipulates a base type can transparently manipulate derived-type objects as well.

If you upcast to an object instead of a pointer or reference, something will happen that may surprise you: the object is .sliced. until all that remains is the subobject that corresponds to the destination type of your cast. In the following example you can see what happens when an object is sliced:

*/

#include <iostream>
using namespace std;

class Pet
{
string pname;

public:
   Pet(const string& p_name) : pname(p_name)
   {
   };

   virtual string name() const { return pname; }

   virtual string description() const { return ("This is " + pname); }

   virtual ~Pet() {}
};

class Dog : public Pet
{

string favoriteActivity;

public:
   Dog(const string& p_name, const string& p_favoriteActivity) : Pet(p_name), favoriteActivity(p_favoriteActivity)
   { };

   string description() const { return (Pet::name() + "likes to" + favoriteActivity); };
};

void describe(Pet p)
{
cout<<p.description()<<endl;
}

int main()
{

 Pet oPet("Alfred");
 Dog oDog("Tommy", "sleep");
 describe(oPet);
 describe(oDog);
 return 0;
}
 
/*

The function describe( ) is passed an object of type Pet by value. It then calls the virtual function description( ) for the Pet object. In main( ), you might expect the first call to produce .This is Alfred,. and the second to produce .Fluffy likes to sleep.. In fact, both calls use the base-class version of description( ).

Two things are happening in this program. First, because describe( ) accepts a Pet object (rather than a pointer or reference), any calls to describe( ) will cause an object of the size of Pet to be pushed on the stack and cleaned up after the call. This means that if an object of a class inherited from Pet is passed to describe( ), the compiler accepts it, but it copies only the Pet portion of the object. It slices the derived portion off of the object, like this:

Now you may wonder about the virtual function call. Dog::description( ) makes use of portions of both Pet (which still exists) and Dog, which no longer exists because it was sliced off! So what happens when the virtual function is called?

You.re saved from disaster because the object is being passed by value. Because of this, the compiler knows the precise type of the object because the derived object has been forced to become a base object. When passing by value, the copy-constructor for a Pet object is used, which initializes the VPTR to the Pet VTABLE and copies only the Pet parts of the object. There.s no explicit copy-constructor here, so the compiler synthesizes one. Under all interpretations, the object truly becomes a Pet during slicing.

Object slicing actually removes part of the existing object as it copies it into the new object, rather than simply changing the meaning of an address as when using a pointer or reference. Because of this, upcasting into an object is not done often; in fact, it.s usually something to watch out for and prevent. Note that, in this example, if description( ) were made into a pure virtual function in the base class (which is not unreasonable, since it doesn.t really do anything in the base class), then the compiler would prevent object slicing because that wouldn.t allow you to .create. an object of the base type (which is what happens when you upcast by value). This could be the most important value of pure virtual functions: to prevent object slicing by generating a compile-time error message if someone tries to do it.

*/
