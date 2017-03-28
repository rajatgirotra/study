/*
 * Please read Sleeping.java first
 * Each thread in JAVA has a priority(integer value) associated with it. You can modify a thread's priority using Thread.setPriority()
 * and fetch it using Thread.getPriority(). The JAVA thread scheduler tends to lean towards executing waiting threads with the highest
 * priority first. This does not mean that the lower priority threads will not execute. It only means that they will execute less often.
 * 
 * On most occasions you will not modify thread priorities. And in many cases modifying a thread priority is usually a mistake.
 */
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class SimplePriorities implements Runnable {
	private int priority;
	private int countdown = 5;
	private volatile double d; //no optimization.

	SimplePriorities(int i) {
		priority = i;
	}
	public String toString() {
		return Thread.currentThread().toString() + ": " + countdown;
	}
	public void run() {
		Thread.currentThread().setPriority(priority);
		while(true) {
			for(int i = 0; i < 100000; ++i) {
				d += (Math.PI + Math.E) / (double)i;
				if(i % 1000 == 0)
					Thread.yield();
			}
			System.out.println(this);
			if(--countdown == 0) return;
		}
	}

	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool();
		for(int i = 0; i < 5; ++i) {
			exec.execute(new SimplePriorities(Thread.MIN_PRIORITY));
			exec.execute(new SimplePriorities(Thread.MAX_PRIORITY));
		}
		exec.shutdown();
	}
}

/*
 * Thread.toString displays the Thread Name, Priority, and the Thread Group. In this case: main.
 * max priority is 10, min is 1, norm is 5.
 * 
 * Mind it that yield() is only a hint to the Thread schedular that the current thread has finished processing some of its work and that
 * it is OK to now run some other thread of the SAME PRIORITY. It is not a guarantee that some other thread will always run.
 * 
 * Please read SimpleDaemons.java next
 */
