/*
 * First java file.
 * Demonstrate the use of PrintStream.printf() and PrintStream.format()
 * JAVA 5 provides C like printf() function to the PrintStream class. Very easy to use. Very trivial.
 */
public class SimpleFormat {
	public static void main(String[] args) {
		int x = 78;
		double d = 4.3219807;
		System.out.println("Row 1: [" + x + ", " + d + "]");
		System.out.printf("Row 1[%d %f]\n", x, d);  //out is an object of type PrintStream defined as a static in the System class.
		System.out.format("Row 1[%d %f]\n", x, d);		
	}
}

/*
Both PrintStream.format() & PrintStream.printf() are exactly similar.
Please read Must_Read_1.txt next.
*/