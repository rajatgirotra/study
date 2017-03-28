/*
 * Please read p2.CTwo.java first
 */

//Nesting a class within a method
//Note this is not allowed in C++

import c08.Destination;
import java.util.*;

public class Parcel4 {
	public Destination dest(String s) {
		class PDestination implements Destination {
			private String s;
			PDestination(String s) {
				this.s = s;
			}
			public String readLabel() {
				return s;
			}
		}
		return new PDestination(s);
	}
	
	public static void main(String[] args) {
		Parcel4 pc4 = new Parcel4();
		Destination d = pc4.dest("Germany");
		System.out.println(d.readLabel());
	}
}

/*
The class PDestination is part of dest( ) rather than being part of
Parcel4. (Also notice that you could use the class identifier
PDestination for an inner class inside each class in the same
subdirectory without a name clash.) Therefore, PDestination cannot be
accessed outside of dest( ). Notice the upcasting that occurs in the return
statement—nothing comes out of dest( ) except a reference to
Destination, the base class.

Of course, the fact that the name of the class
PDestination is placed inside dest( ) doesn’t mean that PDestination
is not a valid object once dest( ) returns.

Please read Parcel5.java next
*/
