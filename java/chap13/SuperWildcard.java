/*
 * Please read SuperTypeWildcards.java first
 */

import java.util.ArrayList;
import java.util.List;


public class SuperWildcard {
	
	public static <T> void add(List<? super T> lst, T item) {
		
	}
	public static void main(String[] args) {
		List<Fruit> lstFruit = new ArrayList<Fruit>();
		List<Apple> lstApple = new ArrayList<Apple>();
		List<Orange> lstOrange = new ArrayList<Orange>();
		List<Jonathan> lstJonathan = new ArrayList<Jonathan>();
		
				
		/******************************************************/
		/* fruit is actually a list of some super type of Fruit.
		 * So it is absolutely safe to add a Fruit or any type derived from Fruit
		 * such as Apple, Orange or Jonathan.
		 */
		List<? super Fruit> fruit = lstFruit;
		fruit.add(new Fruit());
		fruit.add(new Apple());
		fruit.add(new Orange());
		fruit.add(new Jonathan());
				
		//The following two are not allowed.
		//See to fruitOne you can also add an Orange (as you have added above, this means that you
		//are adding an orange to a list of apples. Which the compiler cant allow. So it does not
		//allow you the below assignments.
		//List<? super Fruit> fruitOne = lstApple;
		//List<? super Fruit> fruitTwo = lstOrange;
		/******************************************************/
		
		List<? super Apple> apple = lstApple;
		//You can only add an Apple or any sub-type of Apple.
		//apple.add(new Fruit());
		//apple.add(new Orange());
		apple.add(new Apple());
		apple.add(new Jonathan());
		
		//Since, to appleOne you can only add an Apple or a sub-type of Apple, 
		//all these types are safe to go to a Fruit list because Apple extends Fruit.
		//So the below is allowed.
		List<? super Apple> appleOne = lstFruit;
		//List<? super Apple> appleThree = lstJonathan;
		//List<? super Apple> appleTwo = lstOrange; 
		/******************************************************/
		
		//Same reason as above.
		List<? super Orange> orange = lstOrange;
		//orange.add(new Fruit());
		//orange.add(new Apple());
		
		List<? super Orange> orangeOne = lstFruit;
		//List<? super Orange> orangeTwo = lstApple;
		/******************************************************/
	}
}

/*
So finally the conclusion is that 

1] List<? super T> listT = new ArrayList<?>
where ? represents any super class of T.

and

2] listT.add(new Y());
where Y is T or any sub-type of T

Please read GenericWriting.java next
*/
