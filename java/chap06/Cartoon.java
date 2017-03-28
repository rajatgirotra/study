/*
When you create an object of the derived class,
it contains within it a subobject of the base class. This subobject is the
same as if you had created an object of the base class by itself. Its just
that, from the outside, the subobject of the base class is wrapped within
the derived-class object.

Of course, its essential that the base-class subobject be initialized
correctly, and theres only one way to guarantee this: perform the
initialization in the constructor, by calling the base-class constructor,
which has all the appropriate knowledge and privileges to perform the
base-class initialization. Java automatically inserts calls to the base-class
constructor in the derived-class constructor. The following example shows
this working with three levels of inheritance
*/

import java.util.*;

class Art {
	Art() {
		System.out.println("Art c'tor running");
	}
}

class Drawing extends Art {
	Drawing() {
		System.out.println("Drawing c'tor running");
	}
}

class Cartoon extends Drawing {
	/*Cartoon() {
		System.out.println("Cartoon c'tor running");
	}*/
	public static void main(String[] args)
	{
		Cartoon c = new Cartoon();
	}
}

/*
You can see that the construction happens from the base outward, so
the base class is initialized before the derived-class constructors can
access it. Even if you dont create a constructor for Cartoon( ), the
compiler will synthesize a default constructor for you that calls the base
class constructor
*/
