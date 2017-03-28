/*
Please read TestArrays2.java first. 
Using:
System.arrayCopy()
Arrays.fill()
Arrays.asList()
Arrays.toString()
*/
import java.util.*;

public class CopyingArrays {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		int[] i = new int[7];
		int[] j = new int[10];
		Arrays.fill(i, 43);
		Arrays.fill(j, 99);
		System.out.println("i: " + Arrays.toString(i));
		System.out.println("j: " + Arrays.toString(j));
		System.arraycopy(i, 0, j, 3, i.length-4); //src, srcPos, dest, destPos, length;
		//System.arraycopy(j, 0, i, 0, j.length); // will throw an exception because j.length > destination array size.
		System.out.println("i: " + Arrays.toString(i));
		System.out.println("j: " + Arrays.toString(j));
		
		System.out.println("***************************");
		
		Integer[] a = new Integer[4];
		Integer[] b = new Integer[5];
		Arrays.fill(a, 34);
		System.arraycopy(a, 0, b, 0, a.length);
		System.out.println("a: " + Arrays.toString(a));
		System.out.println("b: " + Arrays.toString(b));
		System.out.println("***************************");
		
		a[2] = 50;
		System.out.println("a: " + Arrays.toString(a));
		System.out.println("b: " + Arrays.toString(b));
		System.out.println("***************************");
		
		//asList() will only return the elements of the Array in the form of a list.
		//The objects are still the same. Any change made to the list will effect the
		//underlying array.
		List lst = Arrays.asList(a);
		//Changes to the list write through to the array.
		lst.set(1, 0);
		System.out.println("Array a as list: " + lst);
		System.out.println("Array a as list: " + Arrays.toString(a));
	}
}

/*
if you copy arrays of objects then only the references get copied—there’s no duplication of
the objects themselves. This is called a shallow copy.
Please read ComparingArrays.java next
*/