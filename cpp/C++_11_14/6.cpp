/*
 * C++ also changes how enums are used to make them more strongly typed. and more strongly scoped. In C++03, it was possible to compare different enums as the compiler
 * also compared the respective integer values.
 *
 * Old-style C++ enums are essentially integers; they could be compared with integers or with other enums of different types. The thing is, you normally
 * don't want to do that since enums are supposed to be some fixed list of enumerated values. Why would you want to compare to some other enum type
 * (or an integer)? It's like saying, "please compare this kind of nail with this kind of toothbrush." It makes no sense, and you probably don't mean to do it.
 * But old-style C++ enums will happily tell you, "why yes, this nail isn't like this toothbrush" or, worse, they might compare equal because they happen 
 * to share the same underlying integer value ("ah yes, this nail IS a Panasonic electronic toothbrush"). Now, with strongly typed enums, the compiler 
 * will tell you that you're doing it. If you really mean it, you can always use a typecast.
 *
 * Another limitation is that enum values were unscoped--in other words, you couldn't have two enumerations that shared the same name:
 * this code won't compile!
	enum Color {RED, GREEN, BLUE}; 
	enum Feelings {EXCITED, MOODY, BLUE};
 */

#include <iostream>
using namespace std;

int main() {
	enum Color {
		RED,
		BLUE
	};

	enum Fruit {
		BANANA,
		APPLE
	};

	Color a = RED;
	Fruit b = BANANA;

	if(a == b) {
		cout << "a and b are equal" << endl;
	} else {
		cout << "a and b are unequal" << endl;
	}
}
