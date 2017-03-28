/**
 * Please read SimpleCollection.java first
 */

/**
 * @author RGirotra
 *
 */
public class SimpleUtilityFunctions {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		SimpleUtilityFunctions suf = new SimpleUtilityFunctions(); 
		
		// Argument to parseInt should be an integer only.
		//Any alpha numeric, decimal or empty string will throw 
		// a NumberFormatExceptin.
		int i = Integer.parseInt("798");
		System.out.println(i);
		
		//StringBuffer.append() function.
		boolean b = false;
		char c = 'A';
		char ch[] = new char[] {'x', 'y', 'z' };
		double d = 123.45;
		int in = 32;
		StringBuffer sb = new StringBuffer("");
		sb.append(b);
		sb.append(c);
		sb.append(" ");
		sb.append(ch);
		sb.append(d);
		sb.append(in);
		sb.append(suf); // Note this one too. 
		System.out.println(sb);
	}

}

/*
Please read Must_Read_3.txt next
*/