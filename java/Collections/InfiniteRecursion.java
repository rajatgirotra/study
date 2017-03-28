import java.util.List;
import java.util.ArrayList;

/*
 * The JAVA standard container class'es like ArrayList, HashSet etc are also derived from
 * Object and overload the toString() member function. This member function creates and empty
 * String buffer, appends a left bracket "[", then calls String.valueOf(Object) for each object
 * it contains, and separates these using a ", " (comma followed by space) and finally appends a
 * closing bracket. "]". Now see the example below.
 */
public class InfiniteRecursion {
	public String toString() {
		//return "Address of the object is: " + this; // printing this causes a recursive call to toSting()
		return "Address of the object is: " + super.toString(); // Use super.toString() instead.
	}
	
	public static void main(String[] args) {
		List l = new ArrayList();
		l.add(new InfiniteRecursion());
		System.out.println(l.get(0));
	}
}

/*
Please read LinkedStack.java next
*/