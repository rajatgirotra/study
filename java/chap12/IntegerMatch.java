/*
 * Please read hex.java first.
 */
import java.util.*;
public class IntegerMatch {
	public static void main(String[] args) {
		System.out.println("1234".matches("-?\\d+"));
		System.out.println("-6781234".matches("-?\\d+"));
		System.out.println("-678.1234".matches("-?\\d+"));
		System.out.println("+6781234".matches("-?\\d+"));
		
		// a \\+ means a literal +. So (-|\\+)? means zero or one occurrence of - or +
		System.out.println("+6781234".matches("(-|\\+)?\\d+"));
	}
}

/*
note that the complete string from index 0 to index end should match the pattern;
otherwise the result will always be false.
Please read Groups.java next
*/