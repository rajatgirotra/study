/*
 * Please read LinkedStack.java first
 * The only difference is to use a non-static inner class and getting rid of the generic used by the inner-class.
 * So an inner class can use the type parameter(here T) of the outer class.
 */
public class LinkedStack1<T> {
	public class Node {
		T item;
		Node next;
		Node() {
			item = null;
			next = null;
		}
		Node(T item, Node next) {
			this.item = item;
			this.next = next;
		}
		boolean end() {
			return ((item == null) && (next == null));
		}
	}
	
	Node top = new Node();
	void push(T item) {
		top = new Node(item, top);
	}
	
	T pop() {
		T result = top.item;
		if(!top.end())
			top = top.next;
		return result;
	}
	
	public static void main(String[] args) {
		LinkedStack1<String> lss = new LinkedStack1<String>();
		for(String s : "red is ocean the".split(" ")) { 
			lss.push(s);
		}
		String str;
		while((str = lss.pop()) != null) {
			System.out.print(str + " ");
		}
	}
}
