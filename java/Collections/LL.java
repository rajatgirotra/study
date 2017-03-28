/*
 * Please read LinkedStack.java first.
 */
import java.util.*;

public class LL {
	public static void main(String[] args) {
		LinkedList[] ll = new LinkedList[10];	
		for(int i = 0; i < ll.length; ++i)
			System.out.println(ll[i]);

		ll[0] = new LinkedList();
		ll[0].add("ABC");
		ll[0].add("XYZ");
		ll[0].add(78);
		for(int i = 0; i < ll.length; ++i)
			System.out.println(ll[i]);
	}
}

/*
Please read Printer.java next
*/