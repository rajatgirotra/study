/*
 * Please read QueueDemo.java first.
 * First-in, first-out (FIFO) describes the most typical queuing discipline. A queuing discipline is what decides,
 * given a group of elements in the queue, which one goes next. First-in, first-out says that the next element should
 * be the one that was waiting the longest. A priority queue says that the element that goes next is the one with the
 * greatest need (the highest priority). For example, in an airport, a customer might be pulled out of a queue if their
 * plane is about to leave. If you build a messaging system, some messages will be more important than others,
 * and should be dealt with sooner, regardless of when they arrive. The PriorityQueue was added in Java SE5
 * to provide an automatic implementation for this behavior. When you offer( ) an object onto a PriorityQueue,
 * that object is sorted into the queue.5 The default sorting uses the natural order of the objects in the queue,
 * but you can modify the order by providing your own Comparator. The PriorityQueue ensures
 * that when you call peek( ), poll( ) or remove( ), the element you get will be the one with the highest priority.
 */

import java.util.*;
public class PriorityQueueDemo {
	public static void main(String[] args) {
		PriorityQueue<Integer> priorityQueue =	new PriorityQueue<Integer>();
		Random rand = new Random(648);
		for(int i = 0; i < 10; i++)
			priorityQueue.offer(rand.nextInt(i + 10));
		QueueDemo.printQ(priorityQueue);


		List<Integer> ints = Arrays.asList(25, 22, 20,
				18, 14, 9, 3, 1, 1, 2, 3, 9, 14, 18, 21, 23, 25);
		priorityQueue = new PriorityQueue<Integer>(ints);
		QueueDemo.printQ(priorityQueue);

		priorityQueue = new PriorityQueue<Integer>(ints.size(), Collections.reverseOrder());
		priorityQueue.addAll(ints);
		QueueDemo.printQ(priorityQueue);


		String fact = "the quick brown fox jumps over the lazy dog.";
		List<String> strings = Arrays.asList(fact.split("")); //Note the split.
		PriorityQueue<String> stringPQ = new PriorityQueue<String>(strings);
		QueueDemo.printQ(stringPQ);


		stringPQ = new PriorityQueue<String>(strings.size(), Collections.reverseOrder());
		stringPQ.addAll(strings);
		QueueDemo.printQ(stringPQ);


		Set<Character> charSet = new HashSet<Character>();
		for(char c : fact.toCharArray())
			charSet.add(c); // Autoboxing
		PriorityQueue<Character> characterPQ =	new PriorityQueue<Character>(charSet);
		QueueDemo.printQ(characterPQ);
	}
}

/*
You can see clearly that the least integer has the highest priority so it is the first one out of the list.
Please read CollectionSequence.java next.
*/
