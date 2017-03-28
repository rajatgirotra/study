/*
 * Please read Must_Read_2.txt first
 */
import java.util.regex.*;
public class TestRegularExpressions {
	private static String input = "Java now has regular expressions";
	private static String regex_2 = "(?i)((^[aeiou])|(\\s+[aeiou]))\\w+?[aeiou]\\b";
	//The regex above tells to:
	//?i - ignore case
	//(^[aeiou])|(\\s+[aeiou]) - Anything starting from a,e,i,o,u or a whitespace followed by a,e,i,o,u
	//\\w+ - followed by one or more alphabets
	//[aeiou] - followed by a,e,i,o,u
	//\\b - at word boundry, ie, the a,e,i,o,u should be the last word in the alphabet.
	
	private static String input_2 = "Arline ate eight apples and one orange while Anita hadn’t any";
	public static void main(String[] args) {
		for(String arg : args) {
			System.out.println("Regular expression: " + arg);			
			Pattern p = Pattern.compile(arg);
			Matcher m = p.matcher(input);
			while(m.find()) {
				System.out.println("Found pattern: " + m.group() + "  at position [ " + m.start() + ", " + (m.end()-1) + " ]");

			}
			System.out.println();
		}
		
		System.out.println("New Input: " + input_2);
		System.out.println("New Regular expression: " + regex_2);
		Pattern p = Pattern.compile(regex_2);
		Matcher m = p.matcher(input_2);
		while(m.find()) {
			System.out.println("Found pattern: " + m.group() + "  at position [ " + m.start() + ", " + (m.end()-1) + " ]");

		}		
	}
}

/* 

Run it like this:
TestRegularExpressions ^Java
TestRegularExpressions \Breg.* 
TestRegularExpressions \breg.*
TestRegularExpressions n.w\s+h(a|i)s
TestRegularExpressions s?
TestRegularExpressions s+
TestRegularExpressions s*

Arline ate eight apples and one orange while Anita hadn’t any

please read turtle.java next
*/
