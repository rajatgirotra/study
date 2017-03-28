import java.util.Random;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read FixedDiningPhilosophers.java first
 * JAVA 5 provides a number of helper classes that enable you to write robust threading applications.
 * One such class is the CountDownLatch. This class is initialized with a integer values. Threads can then call, the
 * CountDownLatch.countDown() to decrement the initial value. When the count reaches zero, all threads that had called
 * CountDownLatch.await() will be unblocked. and all CountDownLatch.await() calls after the value has become zero will 
 * never block. Also, you cannot reset the value of the count once it is initialized. You can basically use this class
 * if you have one or more tasks that have to wait for another set of operations to complete. 
 */

class TaskPortion implements Runnable {
	private static int counter = 0;
	private final int id;
	private CountDownLatch latch = null;
	private Random rand = new Random();
	public TaskPortion(CountDownLatch cdl) {
		//The main thread will create one CountDownLatch object which will be used
		//by all the TaskPortion objects.
		latch = cdl;
		id = counter++;
	}
	public void run() {
		try {
			doWork();
			latch.countDown();
			System.out.println(this + "finished working");
			//System.out.println("CountDownLatch: " + latch);
		} catch(InterruptedException e) {
			System.out.println(this + " interrupted");
		}
	}
	private void doWork() throws InterruptedException {
		TimeUnit.MILLISECONDS.sleep(rand.nextInt(2000));
	}
	public String toString() {
		return String.format("%1$-3d ", id);
	}
}

class WaitingTask implements Runnable {
	private static int counter = 0;
	private final int id;
	private CountDownLatch latch = null;
	//The main thread will create one CountDownLatch object which will be used
	//by all the WaitingTask objects.
	public WaitingTask(CountDownLatch cdl) {
		latch = cdl;
		id = counter++;
	}
	public void run() {
		try {
			latch.await();
			System.out.println("Latch barrier passed for " + this);
		}catch(InterruptedException e) {
			System.out.println(this + " interrupted");
		}
	}
	public String toString() {
		return String.format("WaitingTask %1$-3d ", id);
	}	
}
public class CountDownLatchDemo {
	public static void main(String[] args) throws Exception {
		final int SIZE = 100;
		CountDownLatch cdl = new CountDownLatch(SIZE);
		ExecutorService exec = Executors.newCachedThreadPool();
		System.out.println("Launching all tasks");
		for(int i = 0; i < 10; ++i) {
			exec.execute(new WaitingTask(cdl));
		}
		for(int i = 0; i < SIZE; ++i) {
			exec.execute(new TaskPortion(cdl));
		}
		exec.shutdown();
	}
}

/*
 * the other point to note here is that Random.nextInt() is called by multiple threads. So is it thread-safe?
 * Most of the times you'll have to either google or look inside the JAVA library code to check if an API is thread-safe 
 * or not.
 * 
 * Random.nextInt() is thread-safe.
 * Please read HorseRace.java next
 */
