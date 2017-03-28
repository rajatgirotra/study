/* 
 * Please read IntegerList.java first
 * Create a stack from a linked list.
 * This is an example of a generic class i.e. you are telling the compiler that you are creating a 
 * parameterized class.
 */
import java.util.*;
public class Stack<T> {
	private LinkedList<T> stackList = new LinkedList<T>();
	
	public ListIterator<T> listIterator() {
		return stackList.listIterator();
	}
	
	public void push(T item) {
		stackList.addFirst(item);
	}
	public T pop() {
		try {
			return stackList.removeFirst();		
		}catch (NoSuchElementException e){
			System.err.println("Pop() called but no more elements in the list");
		}
		return null;
	}
	
	public boolean isEmpty() {
		return stackList.isEmpty();
	}
	
	public static void main(String[] args) {
		Stack<Integer> intStack = new Stack<Integer>();
		for(int i = 0; i < 10; ++i) {
			intStack.push(i);
		}
		
		for(int i = 0; i < 15; ++i) {
			System.err.println(intStack.pop());
		}		
	}
}

/*
Please read UniqueWords.java next
*/