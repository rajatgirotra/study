/*
 * Please read PriorityQueueDemo.java first.
 * Demonstrate how to implement a Collection interface.
 * To create an unmodifiable collection, the class must implement the iterator() and size()
 * methods.
 * To create a modifiable collection, the class must additionally implement the add() method
 * and the iterator must implement the remove() method.
 */

import java.util.*;
import typeinfo.pets.*;

class InterfaceVsIterator {
	public static void display(Collection<Pet> pets) {
		for(Pet d : pets) {
			System.out.println(d.id() + ": " + d);
		}
	}
	
	public static void display(Iterator<Pet> iter) {
		while(iter.hasNext()) {
			Pet d = iter.next();
			System.out.println(d.id() + ": " + d);
		}
	}
}

public class CollectionSequence extends AbstractCollection<Pet> {
	private Pet[] pets = Pets.createArray(5);
	
	public Iterator<Pet> iterator() {
		return new Iterator<Pet>() {
			private int index = 0;
			public boolean hasNext() {
				return index < pets.length;
			}
			public Pet next() {
				return pets[index++];
			}
			public void remove() {
				throw new UnsupportedOperationException();
			}
		};
	}
	public int size() {
		return pets.length;
	}
	
	public static void main(String[] args) {
		CollectionSequence c = new CollectionSequence();
		InterfaceVsIterator.display(c);
		InterfaceVsIterator.display(c.iterator());
	}
}

/*
Please read IterableClass.java next
*/