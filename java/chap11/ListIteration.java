/* 
 * Please read SimpleIteration.java first.
 * A subtype of Iterator is the ListIterator which is available only for lists.
 * The advantage is that it is bi-directional unlike Iterator which is unidirectinal.
 * It has interfaces such as hasPrevious(), etc etc.
 */

import typeinfo.pets.*;
import java.util.*;
public class ListIteration {
	public static void main(String[] args) {
		List<Pet> petList = Pets.arrayList(12);
	
		//print the list first.
		System.out.println("Unordered list:" + petList);
		
		//demonstrate next(), hasNext() & nextIndex()
		ListIterator<Pet> petListIter = petList.listIterator();
		System.out.println("Initial value of nextIndex(): " + petListIter.nextIndex()); // Initially zero
		while(petListIter.hasNext()) {
			System.out.println("Index " + petListIter.nextIndex() + " Value: " + petListIter.next());
		}
		System.out.println("value of nextIndex() after reaching the end: " + petListIter.nextIndex());
		System.out.println("value of hasNext() after reaching the end: " + petListIter.hasNext());
		
		//Now traverse back.
		//Demonstrate previous(), hasPrevious() and previousIndex()
		System.out.println("Initial value of previousIndex(): " + petListIter.previousIndex()); // Initially zero
		while(petListIter.hasPrevious()) {
			System.out.println("Index " + petListIter.previousIndex() + " Value: " + petListIter.previous());
		}
		System.out.println("value of previousIndex() after reaching the start: " + petListIter.previousIndex());
		System.out.println("value of hasPrevious() after reaching the start: " + petListIter.hasPrevious());
		
		//Demonstrate remove(), set() and add()
		//remove() will remove the element that was last returned by a call to next() or previous()
		petListIter = petList.listIterator();
		System.out.println("Calling next 5 times followed by previous(). This should remove the element at index 4:");
		for(int i = 0; i < 5; ++i)
			petListIter.next();
		petListIter.previous();
		//petListIter.add(new Pet("Dog")); //There should not be a call to add() between a call to next() or previous() and remove().
		//Uncomment the above line to get an IllegalStateException.
		petListIter.remove();
		System.out.println("List now after calling remove:" + petList);		
		
		//Demonstrate add()
		//add() adds a new element to a list immediately before the next element that would be returned by next()
		//and after the next() element that would be returned by previous(). The element is added before the last the implicit cursor.
		//That is a call to next() will be unaffected but a call to previous will return the new element in the list.
		//It also increases by one the value returned by nextIndex() and previousIndex().
		System.out.println("List before add: " + petList);
		System.out.println("Adding a new Hamster at the beginning: ");
		petListIter = petList.listIterator();
		petListIter.add(new Hamster());
		System.out.println("List after add: " + petList);
		
		//Demonstrate set()
		//set() updates the last element returned by next() or previous(). There should be no call to add() or
		//remove() between calls to next() or previous() and set().
		System.out.println("List before Set" + petList);
		petListIter = petList.listIterator();
		//petListIter.set(new Manx()); // you get an exception here, because neither next() or previous() were called.
		//Uncomment the above line to see what happens.
		petListIter.next();
		petListIter.set(new EgyptianMau());
		System.out.println("List after Set" + petList);
	}
}

/*
Please read IntegerList.java next
*/