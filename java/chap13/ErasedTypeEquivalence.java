/*
 * Please read Must_Read_1.txt first
 */
import java.util.*;
public class ErasedTypeEquivalence {
	public static void main(String[] args) {
		
		//This is always invalid. You can never use a generic type with the "class" literal. Because ArrayList<Integer> is no class in JAVA.
		//But ArrayList is; so ArrayList.class is valid.
		//System.out.println(ArrayList<Integer>.class);
		
		Class c1 = new ArrayList<String>().getClass();
		Class c2 = new ArrayList<Integer>().getClass();
		System.out.println(c1 == c2);
		System.out.println(c1);
	}
}
/*
Please read LostInformation.java next
*/