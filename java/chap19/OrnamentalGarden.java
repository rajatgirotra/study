import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read ThreadLocalVariableHolder.java first
 */

class Count {
	private int count = 0;
	private Random rand = new Random(47);
	public synchronized int increment() {
		int temp = count;
		if(rand.nextBoolean()) {
			Thread.yield();
		}
		return (count = ++temp);
	}
	
	public synchronized int value() {
		return count;
	}
}

class Entrances implements Runnable {
	private static Count count = new Count();
	private int number = 0;
	private final int id;
	private static List<Entrances> entrances = new ArrayList<Entrances>();
	private static volatile boolean cancelled = false;
	public Entrances(int idn) {
		id = idn;
		entrances.add(this);
	}
	
	public static void cancel() { 
		cancelled = true;
	}
	public void run() {
		while(!cancelled) {
			//synchronized(this) {
				++number;
			//}
			System.out.println(this + "  TotalCount: " + count.increment());
		}
		System.out.println("Stopping " + this);
	}
	public String toString() {
		return "Entrance " + id + " Number " + number;
	}
	public static int getTotalCount() {
		return count.value();
	}
	public static int sumEntrances() {
		int sum = 0;
		for(Entrances e : entrances) {
			sum += e.number;
		}
		return sum;
	}
}
public class OrnamentalGarden {
	public static void main(String[] args) throws Exception {
		ExecutorService exec = Executors.newCachedThreadPool();
		for(int i = 0; i < 5; ++i) {
			exec.execute(new Entrances(i));
		}
		try {
			TimeUnit.SECONDS.sleep(3);
		}catch (InterruptedException ignore) {}
		Entrances.cancel();
		exec.shutdown();
		if(!exec.awaitTermination(250, TimeUnit.MILLISECONDS)) {
			System.out.println("Some of the tasks did not finish successfully");
		}
		System.out.println("Total: " + Entrances.getTotalCount());
		System.out.println("Sum of Entrances: " + Entrances.sumEntrances());
	}
}

/*
Please read Must_Read_3.txt next
*/