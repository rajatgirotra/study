/*
 * Read TestRegularExpressions.java first.
 * Demonstrate the use of Formatter class.
 * JAVA 5 introduced a new class Formatter. This class is used to format your string output as you would like.
 * You can tell a Formatter where the output should go at the time of constructing it. See a trivial example below:
 */
import java.util.*;
import java.io.*;
public class Turtle {
	
	private String name;
	private Formatter f;
	
	public Turtle(String name, Formatter f) {
		this.name = name;
		this.f = f;
	}
	
	public void move(int x, int y) {
		/* %[argument_index$][flags][width][.precision]conversion */
		f.format("%3$-10s The turtle is at [ %1$10d %1$-10d ]\n", y, x, name);
	}
	public static void main(String[] args) {
		PrintStream outAlias = System.out;
		Turtle tommy = new Turtle("Tommy", new Formatter(System.err));
		Turtle harry = new Turtle("Harry", new Formatter(System.err));
		tommy.move(1, 3);
		harry.move(7, 8);
		harry.move(2, 4);
		tommy.move(1, 0);
	}
}

/*
 The format specifier format is:
 
 %[argument_index$][flags][width][.precision]conversion
 
 Often, you’ll need to control the minimum size of a field. This can be accomplished by specifying a width. The Formatter guarantees
 that a field is at least a certain number of characters wide by padding it with spaces if necessary. By default, the data
 is right justified, but this can be overridden by including a ‘-’ in the flags section.
 The opposite of width is precision, which is used to specify a maximum. Unlike the width, which is applicable to all of
 the data conversion types and behaves the same with each, precision has a different meaning for different types.
 For Strings, the precision specifies the maximum number of characters from the String to print. For floating point numbers,
 precision specifies the number of decimal places to display (the default is 6), rounding if there are too many or adding
 trailing zeroes if there are too few. Since integers have no fractional part, precision isn’t applicable to them and you’ll get
 an exception if you use precision with an integer conversion type.
 
 please read DatabaseException.java next
*/