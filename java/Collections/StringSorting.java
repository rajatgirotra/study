/*
 * Please read CompType.java first.
 * Here’s an example that generates random String objects and sorts them:
 */

import com.rajatgirotra.util.*;
import java.util.*;

public class StringSorting {
	public static void main(String[] args) {
		String[] str = new String[10];
		Arrays2.fill(str, new Arrays2.RandStringGenerator(5));
		System.out.println("before sort str: " + Arrays.asList(str));
		Arrays.sort(str);
		System.out.println("after sort str: " + Arrays.asList(str));
	}	
}

/*
Please read Reverse.java next
*/