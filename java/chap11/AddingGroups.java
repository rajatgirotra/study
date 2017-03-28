/*
 * Please read SimpleCollection.java first.
 */
import java.util.*;
public class AddingGroups {
	public static void main(String[] args) {
		Collection<Integer> coll = new ArrayList<Integer>(Arrays.asList(1,2,3,4,5));
		Integer[] moreInts = {6,7,8,9,10};
		Collections.addAll(coll, moreInts);
		for(Integer c : coll) {
			System.out.println(c);
		}
		coll.clear();
		
		//Making a Collection in a faster way.
		Collections.addAll(coll, 1, 2, 3, 4 ,5);
		for(Integer c : coll) {
			System.out.println(c);
		}
		
		//Create a List backed by an array. 
		List<Integer> li = Arrays.asList(1,2,3,4,5);
		li.set(1, 99);
		
		//You get an exception at this line as the list as backed by an array which is fixed in size.
		//so you cannot add any new elements to the list.
		li.add(45);
		
	}
}

/*
Please read AsListInterface.java next
*/