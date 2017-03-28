/*
To understand how JAVA implements RTTI, you need to understand the Class Object. The Class
object is a special object that is used to create objects of your class.

Whenever you create a new class in JAVA and you compile it, a special Class object also gets 
constructed and is stored in the corresponding .class file.

Whenever ur code later creates an object of that class or references any static method or variable
the Java Virtual Machine checks if the corresponding class object is loaded in memory of not.
If not the corresponding class object is loaded in memory, and the static initializers are run
just once. Then the procedure is same as in chap04/Must_Read_5.txt 
 */

import java.util.*;

class Candy {
	static {
		System.out.println("Candy!!");
	}
}

class Cookie {
	static {
		System.out.println("Cookie!!");
	}
}

class Gum {
	static {
		System.out.println("Gum!!");
	}
}
public class SweetShop {
	public static void main(String[] args) {
		System.out.println("inside main");
		new Candy();
		System.out.println("after creating new Candy!!");
		try {
			Class.forName("Gum");			
		}catch (ClassNotFoundException e) {
			System.out.println("Class Gum not found!!");
		}
		new Cookie();
		System.out.println("after creating new Cookie!!");		
	}
}

/*
Each of the classes Candy, Gum, and Cookie have a static clause that is
executed as the class is loaded for the first time. Information will be
printed to tell you when loading occurs for that class.

A particularly interesting line is:
Class.forName("Gum");

This method is a static member of Class (to which all Class objects
belong). A Class object is like any other object and so you can get and
manipulate a reference to it (that’s what the loader does). One of the ways
to get a reference to the Class object is forName( ), which takes a
String containing the textual name (watch the spelling and
capitalization!) of the particular class you want a reference for. It returns
a Class reference, which is being ignored here—the call to forName( ) is
being made for its side effect, which is to load the class Gum if it isn’t
already loaded. In the process of loading, Gum’s static clause is
executed.

*/
