/*
 * Please read CatsAndDogs2.java first
 */
import java.util.*;

public class FillingArrays {
	public static void main(String[] args) {
		int size = 6;
		if(args.length > 0)
			size = Integer.parseInt(args[0]);
		
		char[] c = new char[size];
		byte[] b = new byte[size];
		short[] s = new short[size];
		int[] i = new int[size];
		long[] l = new long[size];
		float[] f = new float[size];
		double[] d = new double[size];
		boolean[] bo = new boolean[size];
		
		//Using the default Arrays class
		//The problem with this is that it will fill the array will only one element
		//specified in the argument list. to overcome this we have written our own Arrays2.java class
		Arrays.fill(c, 'd');
		Arrays.fill(b, (byte)23);
		Arrays.fill(s, (short)8);
		Arrays.fill(i, -9779);
		Arrays.fill(l, 1234567890);
		Arrays.fill(f, -0.9876f);
		Arrays.fill(d, 12345678.98765432);
		Arrays.fill(bo, true);
		
		//Using the JAVA Arrays.toString() method. prints [blah, blah, ...]
		System.out.println("Char: " + Arrays.toString(c));
		System.out.println("Byte: " + Arrays.toString(b));
		System.out.println("Short: " + Arrays.toString(s));
		System.out.println("Int: " + Arrays.toString(i));		
		System.out.println("Long: " + Arrays.toString(l));		
		System.out.println("Float: " + Arrays.toString(f));		
		System.out.println("Double: " + Arrays.toString(d));		
		System.out.println("Boolean: " + Arrays.toString(bo));		
	}
}

/*
Please read FillingLists.java next
*/