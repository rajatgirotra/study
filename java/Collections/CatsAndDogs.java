/*
 * Please read Dog.java first
 */
import java.util.ArrayList;
import java.util.List;

public class CatsAndDogs {
	public static void main(String[] args) {
		List cats = new ArrayList();
		for(int i = 0; i < 7; ++i) {
			cats.add(new Cat(i));
		}
		cats.add(new Dog(7));
		
		for(int i = 0; i < cats.size(); ++i) {
			((Cat)cats.get(i)).print();
		}			
	}
}

/*
The classes Cat and Dog are distinct—they have nothing in common
except that they are Objects. (If you don’t explicitly say what class you’re
inheriting from, you automatically inherit from Object.) Since
ArrayList holds Objects, you can not only put Cat objects into this
container using the ArrayList method add( ), but you can also add Dog
objects without complaint at either compile time or run time. When you
go to fetch out what you think are Cat objects using the ArrayList
method get( ), you get back a reference to an object that you must cast to
a Cat. Then you need to surround the entire expression with parentheses
to force the evaluation of the cast before calling the print( ) method for
Cat, otherwise you’ll get a syntax error. Then, at run time, when you try to
cast the Dog object to a Cat, you’ll get an exception

Please read CatsAndDogs2.java next
*/