/*
 * Please read InfiniteRecursion.java first.
 *  Create a stack from a linked list
 */  

import java.util.*;

class Stack {
	private LinkedList stk = new LinkedList();
	
	public void push(Object obj) {
		stk.addFirst(obj);
	}
	
	Object pop() {
		if(stk.size() > 0) {
			return stk.removeFirst();			
		}
		else {
			System.out.println("Stack Empty!! returning null");
			return null;
		}			
	}
	
	boolean isEmpty() {
		if(stk.size() == 0)
			return true;
		else
			return false;
	}
}

public class LinkedStack {
	
	public static void main(String[] args) {
		Stack stack = new Stack();
		stack.push("ABC");
		stack.push("PQR");
		
		while(!stack.isEmpty()) {
			System.out.println(stack.pop());
		}		
	}
}

/*
Please read LL.java next
*/