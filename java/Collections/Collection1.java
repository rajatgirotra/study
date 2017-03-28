/*
 * Please read Collections2.java first
 *  Understand Collection functionality 
 */

import java.util.*;
import com.rajatgirotra.util.*;

public class Collection1 {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		Collection c = new ArrayList();
		
		Collections2.fill(c, Collections2.countries, 5);
		System.out.println("1: " + c);
		
		c.add("Ten");
		c.add("Eleven");
		System.out.println("2: " + c);
		
		Collection c2 = new ArrayList();
		Collections2.fill(c2, Collections2.capitals, 5);
		c.addAll(c2);
		System.out.println("3: " + c);
		
		c.clear();
		System.out.println("4: " + c);
		
		Collections2.fill(c, Collections2.countries, 10);
		System.out.println("5: " + c);
		System.out.println("6: " + c.contains("DJIBOUTI"));
		System.out.println("7: " + c.contains("Eleven"));
		
		c2.clear();
		System.out.println("8: " + c2.isEmpty());
		
		//c2.add("Ten");
		c2.add("CAMEROON");
		c2.add("COMOROS");
		System.out.println("9: " + c.containsAll(c2));
		
		Printer.printAll(c.iterator());
	}
}

/*
Please read Cat.java next
*/