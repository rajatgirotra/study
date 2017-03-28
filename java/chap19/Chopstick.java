/*
 * Please read PipedIO.java first
 * We will now demonstrate how a deadlock can occur when multiple tasks are trying to share resources.
 * A deadlock situation occurs when mutiple thread P1..P2..P3..P4..Pn..P1 are all waiting for an event to occur which
 * can only be caused by a task which is already waiting.
 * 
 *  We use the classic Dining Philosophers problem: 
 *  There are 5 philosophers sitting on a round table with a bowl of spaghetti in the middle. Each philosopher either
 *  thinks or eats. There are 5 chopsticks (same number as the no. of philosophers) placed on the left and right of each
 *  philosopher. When a philosopher is thinking, he doesn't need any resources but when he is eating, he grabs the right
 *  chopstick, then the left one, and eats for a while. He then drops them and starts thinking again.
 */
public class Chopstick {
	private volatile boolean taken = false;
	public synchronized void take() throws InterruptedException	{
		while(taken)
			wait();
		taken = true;
	}
	public synchronized void drop() {
		taken = false;
		notifyAll();
	}
}

/*
Please read Philosopher.java next
*/