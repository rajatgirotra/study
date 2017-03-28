/*
 * Please read TestRegularExpression.java first
 * Demonstrate the use of the Scanner class.
 */

import java.io.*;
import java.util.*;
public class BetterRead {
	public static BufferedReader br = new BufferedReader(new StringReader("Sir Robin of Camelot\n22 1.61803"));
	public static String str = "Sir Robin of Camelot\n22 1.61803";
	public static void main(String[] args) throws IOException {
		Scanner stdin = new Scanner(br);
		String name = stdin.nextLine();
		int age = stdin.nextInt();
		float f = stdin.nextFloat();
		System.err.println("Name: " + name);
		System.err.println("Age: " + age);
		System.err.println("favourite decimal: " + f);		
	}
}
