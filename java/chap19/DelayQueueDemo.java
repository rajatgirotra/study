import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.DelayQueue;
import java.util.concurrent.Delayed;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import static java.util.concurrent.TimeUnit.*;

/*
 * Please read HorseRace.java first
 * There is another threading aid call DelayedQueue. This is nothing but a blocking queue which holds objects of classes
 * which implement the Delayed interface.
 * The Delayed interface has two methods to implement
 * 
 * long getDelay(TimeUnit unit) --> returns the time delay, after which the task should be run.
 * int compareTo(Delayed arg) --> This one is from the comparable interface extended by the Delayed interface.
 * 
 * The tasks are held in a fashion, that the task which has expired for the longest time is pulled out first from the
 * queue. If no task has expired, then the poll() function will return null. This is also the reason why u cant place null
 * in a delayed queue.
 */

class DelayedTask implements Runnable, Delayed {
	private static int counter = 0;
	private final int id = counter++;
	private final long delta; //the delay in milliseconds;
	private final long trigger; // the time in nanoseconds after which the delay will expire and the task should be run.
	
	//The list will maintain the order in which the DelayesTasks were actually created and added to the DelayedQueue.
	protected static List<DelayedTask> taskList = new ArrayList<DelayedTask>();

	public DelayedTask(long delayInMilli) {
		delta = delayInMilli;
		trigger = System.nanoTime() + NANOSECONDS.convert(delta, MILLISECONDS); //See the static import at the beginning.
		taskList.add(this);
	}

	//Implementing the Delayed Interface first
	public long getDelay(TimeUnit unit) {
		return unit.convert(trigger - System.nanoTime(), NANOSECONDS);
	}
	public int compareTo(Delayed arg) {
		DelayedTask that = (DelayedTask)arg;
		if(trigger < that.trigger) return -1;
		if(trigger > that.trigger) return 1;
		return 0;
	}

	public String toString() {
		return String.format("[%1$-4d]", delta) + " Task " + id;
	}

	public String summary() {
		return "(" + id + ": " + delta +") ";
	}

	//Implement the Runnable interface now
	public void run() {
		System.out.print(this + " ");
	}

	public static class EndSentinel extends DelayedTask {
		private ExecutorService exec;		
		public EndSentinel(long delay, ExecutorService exec) {
			super(delay);
			this.exec = exec;
		}
		public void run() {
			//Print summary of the tasks and then exit.
			for(DelayedTask dt : taskList) {
				System.out.print(dt.summary());				
			}
			System.out.println();
			System.out.println(this + " calling shutdownNow()");
			exec.shutdownNow();
		}
	}
}
class DelayedTaskConsumer implements Runnable {
	private DelayQueue<DelayedTask> q;
	public DelayedTaskConsumer(DelayQueue<DelayedTask> q) {
		this.q = q;
	}
	public void run() {
		try {
			while(!Thread.interrupted())
				q.take().run(); // Run task with the current thread
		} catch(InterruptedException e) {
			// Acceptable way to exit
		}
		System.out.print("Finished DelayedTaskConsumer");
	}
}
public class DelayQueueDemo {
	public static void main(String[] args) {
		Random rand = new Random(47);
		ExecutorService exec = Executors.newCachedThreadPool();
		DelayQueue<DelayedTask> queue =	new DelayQueue<DelayedTask>();
		// Fill with tasks that have random delays:
		for(int i = 0; i < 20; i++)
			queue.put(new DelayedTask(rand.nextInt(5000)));
		// Set the stopping point
		queue.add(new DelayedTask.EndSentinel(5000, exec));
		exec.execute(new DelayedTaskConsumer(queue));
	}
}

/*
Please read PriorityBlockingQueueDemo.java next
*/