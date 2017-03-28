/*
 * Please read ArrayIsNotIterable.java first.
 * Use the JAVA foreach syntax to display a Map.
 */

import java.util.*;

public class EnvironmentVariables {
	public static void main(String[] args) {
		for( Map.Entry entry : System.getenv().entrySet()) {
			System.out.println(entry.getKey() + " : " + entry.getValue());
		}
	}
}
