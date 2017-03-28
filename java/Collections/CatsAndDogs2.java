/*
 * Please read CatsAndDogs.java first 
 */
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/*
 * JAVA Iterators.
 * 1. Ask a container to hand you an Iterator using a method called iterator( ). This Iterator
 * will be ready to return the first element in the sequence on your first call to its next()
 * method.
 * 
 * 2. Get the next object in the sequence with next( ).
 * 
 * 3. See if there are any more objects in the sequence with hasNext( ).
 * 
 * 4. Remove the last element returned by the iterator with remove( ).
 */
public class CatsAndDogs2 {
	@SuppressWarnings("unchecked")
	public static void main(String[] args) {
		List cats = new ArrayList();
		for(int i = 0; i < 7; ++i) {
			cats.add(new Cat(i));
		}
		cats.add(new Dog(7));
		
		Iterator e = cats.iterator();
		while(e.hasNext()) {
			((Cat)e.next()).print();
		}

					
	}
}

/*
Please read FillingArrays.java next
*/