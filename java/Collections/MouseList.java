/* Please read Mouse.java first
 * Making a type-conscious ArrayList
 * You can create a new class using ArrayList(), which can only store objects of a particular 
 * type.
 */

import java.util.*;

public class MouseList {
	private final List mouseList = new ArrayList();
	public void add(Mouse m) {
		mouseList.add(m);
	}
	
	public Mouse get(int i) {
		return (Mouse)mouseList.get(i);
	}
	
	public int size() {
		return mouseList.size();
	}
	
	public static void main(String[] args) {
		MouseList ml = new MouseList();
		for(int i = 0; i < 3; ++i) {
			ml.add(new Mouse(i));
		}
		for(int i = 0; i < ml.size(); ++i) {
			System.out.println(ml.get(i));
		}
	}
}


/*
Because a MouseList will accept only a Mouse, if you say:
ml.add(new Pigeon());
you will get an error message at compile time. This approach, while more
tedious from a coding standpoint, will tell you immediately if you’re using
a type improperly.

Please read Set1.java next
*/