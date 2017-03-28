/*
 * Please read SpringDetector.java first
 */
//: c11:Statistics.java
// Simple demonstration of HashMap.
import java.util.*;
class Counter {
	int i = 1;
	public String toString() { return Integer.toString(i); }
}
public class Statistics {
	private static Random rand = new Random();
	public static void main(String[] args) {
		Map hm = new HashMap();
		for(int i = 0; i < 10000; i++) {
			// Produce a number between 0 and 20:
			Integer r = new Integer(rand.nextInt(4));
			if(hm.containsKey(r))
				((Counter)hm.get(r)).i++;
			else
				hm.put(r, new Counter());
		}
		System.out.println(hm);
	}
}

/*
Please read StringHashCode.java next
*/