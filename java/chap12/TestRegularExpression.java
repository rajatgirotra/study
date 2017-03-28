/*
 * Please read Replacing.java first.
 * Demonstrate the use of Pattern and Matcher objects.
 * You can use the static Pattern compile(String regex) method to first compile a Pattern. This function returns a Pattern
 * object.
 * Then you can apply use the Pattern's matcher() method to get a Matcher object.
 * 
 * Pattern p = Pattern.compile(String regex);
 * Matcher m = p.matcher(String inputString).
 * You can then perform 3 types of searches.
 * 
 * 1] matches()  - attempts to match the entire input to the pattern.
 * 2] lookingAt() - attempts to match the pattern starting at the beginning of the inputString.
 * 3] find() - scans the inputString to search for the next sequence of characters that matched the pattern.
 */
import java.util.regex.Pattern;
import java.util.regex.Matcher;
public class TestRegularExpression {
	public static void main(String[] args) {
		String input = "abcabcabcdefabc";
		String regex = "abc+";
		Pattern p = Pattern.compile(regex);
		Matcher m = p.matcher(input);
		while(m.find()) {
			System.out.println("m.group() = " + m.group() + "  Start: " + m.start() + "  End: " + (m.end()-1));			 
		}
	}
}

/*
please read betterRead.java next
*/