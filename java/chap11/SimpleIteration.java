/*
 * Please read PrintingContainers.java first.
 * this example shows how to use an iterator.
 */
import java.util.*;

class Employee {
	private String name;
	private long empID;
	Employee(String name, long empID) {
		this.name = name;
		this.empID = empID;
	}
	public String toString() {
		return "Name: " + name + "  EmpID: " + empID;
	}
}

class Rank extends Employee {
	private static Random rand = new Random();
	private int rank = rand.nextInt(5);
	public Rank(String name, long empID) {
		super(name, empID);
	}
	public String toString() {
		return (super.toString() + " Rank: " + rank);
	}
}
public class SimpleIteration {
	public static void main(String[] args) {
		List<Rank> ranks = new ArrayList<Rank>();
		ranks.add(new Rank("Rajat", 148));
		ranks.add(new Rank("Prakash", 149));
		ranks.add(new Rank("Puneet", 150));
		ranks.add(new Rank("Aman", 151));
		
		//Create an iterator
		Iterator<Rank> rankIter = ranks.iterator();
		while(rankIter.hasNext()) {
			Rank r = rankIter.next();
			System.out.println(r);
		}
		
		//Using an iterator to remove() an element
		rankIter = ranks.iterator();
		rankIter.next();
		rankIter.remove(); // You must call next() before you call remove();
		//Calling next() for the first time, will simply put the iterator just
		//before the first element. remove() will by default remove the next element().
		
		System.out.println("After removal");
		for(Rank r : ranks) {
			System.out.println(r);
		}
	}
}

/*
Please read ListIteration.java next
*/