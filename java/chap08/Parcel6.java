//Parcel5.java first

// A method that returns an anonymous inner class.
import c08.Contents;

public class Parcel6 {
	public Contents cont() {
		return new Contents() {
			private int i = 11;
			public int value() {
				return i;
			}
			public String toString() {
				return Integer.toString(i);
			}
		}; //semicolon required in this case.
	}
	public static void main(String[] args) {
		Parcel6 pc6 = new Parcel6();
		Contents c = pc6.cont();
		System.out.println(c);
	}
}

/*
The cont( ) method combines the creation of the return value with the
definition of the class that represents that return value! In addition, the
class is anonymous—it has no name. To make matters a bit worse, it looks
like you’re starting out to create a Contents object.

return new Contents()
But then, before you get to the semicolon, you say, “But wait, I think I’ll
slip in a class definition”:

return new Contents() {
private int i = 11;
public int value() { return i; }
};
What this strange syntax means is: “Create an object of an anonymous
class that’s inherited from Contents.” The reference returned by the new
expression is automatically upcast to a Contents reference. The
anonymous inner-class syntax is a shorthand for:
class MyContents implements Contents {
private int i = 11;
public int value() { return i; }
}
return new MyContents();


if you have a look at Parcel4 again, you'll realise that they are almost the same.
the only difference being that the inner class there had a name, which was anyways not
accessible outside the scope. So better not to have a class name. :)

Parcel7.java next
*/
