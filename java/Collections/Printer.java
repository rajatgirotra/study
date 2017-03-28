/* Please read LL.java first
 * Generic printer class to print any List using Iterators.
 * The object should override the toString() member function.
 */

import java.util.Iterator;
public class Printer {
	public static void printAll(Iterator e) {
		while(e.hasNext()) {
			System.out.println(e.next());
		}
	}
}

/*
Please read PrintingContainers.java next
*/