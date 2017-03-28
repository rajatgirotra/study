/* 
 * Read Must_read_1.txt first.
 * In this program, since the ArrayList() container does not use generics, the compiler will give you a warning.
 * For now, you can compress this warning using a Java SE-5 annotation. An annotation begins with an "@" sign followed
 * by an argument. In this case we use @SuppressWarnings to suppress "unchecked" warnings only.
 */

import java.util.*;

class Apple {
	private static long counter = 0;
	private long id = counter++;
	public long id() {
		return id;
	}
}

class Orange { 
}
public class ApplesAndOrangesWithoutGenerics {
	@SuppressWarnings("unchecked") // here the annotation is added at the beginning of the function.
	public static void main(String[] args) {
		ArrayList list = new ArrayList();
		for (int i = 0; i < 5; ++i)
			list.add(new Apple());
		
		//add an orange
		list.add(new Orange());
		
		//Now print the id's
		for(int i = 0; i < list.size(); ++i)
			System.err.println(((Apple)list.get(i)).id());
	}
}

/*
 * In the Generics chapter, you’ll learn that creating classes using Java generics can be complex. However, applying
 * predefined generic classes is usually straightforward. For example, to define an ArrayList intended to hold Apple
 * objects, you say ArrayList<Apple> instead of just ArrayList. The angle brackets surround the type parameters
 * (there may be more than one), which specify the type(s) that can be held by that instance of the container. With
 * generics, you’re prevented, at compile time, from putting the wrong type of object into a container. The program 
 * ApplesAndOrangesWithGenerics.java uses generics.
 * 
 * Please read ApplesAndOrangesWithGenerics.java next
 */
