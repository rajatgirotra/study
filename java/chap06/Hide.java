/*
If a Java base class has a method name thats overloaded several times,
redefining that method name in the derived class will not hide any of the
base-class versions (unlike C++). Thus overloading works regardless of
whether the method was defined at this level or in a base class:
*/

import java.util.*;

class Homer {
	char doh(char c) {
		System.out.println("doh(char)");
		return 'd';
	}
	float doh(float f) {
		System.out.println("doh(float)");
		return 1.0f;
	}
}

class Milhouse { }

class Bart extends Homer {
	void doh(Milhouse m) {
		System.out.println("doh(Milhouse)");
	}
}

class Hide {

	public static void main(String[] args) {
		Bart b = new Bart();
		b.doh(1);
		b.doh('x');
		b.doh(1.0f);
		b.doh(new Milhouse());
	}
}

/*
You can see that all the overloaded methods of Homer are available in
Bart, even though Bart introduces a new overloaded method (in C++
doing this would hide the base-class methods). As youll see in the next
chapter, its far more common to override methods of the same name,
using exactly the same signature and return type as in the base class. It
can be confusing otherwise (which is why C++ disallows it, to prevent you
from making what is probably a mistake).
*/
