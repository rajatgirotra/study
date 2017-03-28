/*
 * Please read groups.java first.
 */
import java.util.*;

public class Splitting {
	public static String knights =
		"Then, when you have found the shrubbery, you must " +
		"cut down the mightiest tree in the forest... " +
		"with... a herring!";
	public static void split(String regex) {
		System.out.println(
				Arrays.toString(knights.split(regex)));
	}
	public static void main(String[] args) {
		split(" "); // Doesn’t have to contain regex chars
		split("\\W+"); // Non-word characters, so a ", " i.e. a comma followed by a space are non-word characters.
		split("n\\W+"); // ‘n’ followed by non-word characters. The output should be clear from above comment.
		split("the|you"); //splitting the string on the or you.
	}
}

/*
String.split(String regex) returns an array of String[] objects around matches of the given regular expression.
Arrays.toString(Object[]) returns a String containing the elements in the Object[] array.

Please read Replacing.java next
*/