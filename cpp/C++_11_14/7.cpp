/*
 * In C++0x11, c++ introduces enum class which makes enums both strongly typed and strongly scoped.
 */

#include <iostream>
using namespace std;

int main()
{
    //enum class Color
    enum struct Color // or enum struct, both are same.
    {
        RED,
        BLUE,
	ORANGE
    };
 
    enum class Fruit
    {
        BANANA,
        APPLE,
	ORANGE
    };

    //Note that ORANGE is both a Color and a Fruit.
    //The use of the word class is meant to indicate that each enum type really is different and not comparable to other enum types.
    //Strongly typed enums, enum classes, also have better scoping. Each enum value is scoped within the name of the enum class. In other words,
    //to access the enum values, you must write:
 
    Color a = Color::RED; // note: RED is not accessible any more, we have to use Color::RED
    Fruit b = Fruit::BANANA; // note: BANANA is not accessible any more, we have to use Fruit::BANANA
 
    #if 0
    if (a == b) // compile error here, as the compiler doesn't know how to compare different types Color and Fruit
        cout << "a and b are equal" << endl;
    else
        cout << "a and b are not equal" << endl;
    #endif 
 
    return 0;
}

/*
 * Enum classes have another advantages over old-style enums. You can have a forward declaration to a strongly typed enum, meaning that you can write code like:
 *
 * enum class Mood;
 *  
 * void assessMood (Mood m);
 *    
 * later on:
	enum class Mood { EXCITED, MOODY, BLUE };


 * Another advantage is that an enum can now have size. Default is integer, but you can specify char, long, unsigned long etc. Like this.
 *
 * enum class Colors : char
 * {
 * 	A,
 * 	B,
 * 	C
 * };
 *
 * So you can have upto sizeof(char) entries in your enum.
 */
