/* 
 * Please read MapOfList.java first.
 * Queues are commonly used as a way to reliably transfer objects from one area of a program to another.
 * Queues are especially important in concurrent programming, as you will see in the Concurrency chapter,
 * because they safely transfer objects from one task to another. LinkedList has methods to support queue
 * behavior and it implements the Queue interface, so a LinkedList can be used as a Queue implementation.
 * By upcasting a LinkedList to a Queue, this example uses the Queue specific methods in the Queue interface:
 */
import java.util.*;
public class QueueDemo {
	public static void printQ(Queue queue) {
		while(queue.peek() != null)
			System.out.print(queue.remove() + " ");
		System.out.println();
	}
	public static void main(String[] args) {
		Queue<Integer> queue = new LinkedList<Integer>();
		Random rand = new Random(478);
		for(int i = 0; i < 10; i++)

			queue.offer(rand.nextInt(i + 10));
		printQ(queue);
		Queue<Character> qc = new LinkedList<Character>();
		for(char c : "Brontosaurus".toCharArray())
			qc.offer(c);
		printQ(qc);
	}
}

/*
 * Please read PriorityQueueDemo.java next
 */
