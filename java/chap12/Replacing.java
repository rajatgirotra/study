/*
 * Please read splitting.java first.
 */
public class Replacing {
	public static void main(String[] args) {
		String temp = Splitting.knights;
		
		System.out.println("Original: " + temp);
		System.out.println(temp.replaceFirst("f\\w+", "located"));
		System.out.println(temp.replaceAll("shrubbery|tree|herring", "banana"));
	}
}
/*
Please read  testRegularexpression.java next
*/