import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;

/*
 * Please read AtomicEvenGenerator.java first
 * CriticalSection is a piece of code that must be executed by only one task at a time.
 * The code must guarantee serial access to critical sections. This can be done using the synchronized 
 * keyword by synchronizing the "this" object. In this program we show that it is a good practice to
 * synchronize on the "this" object instead of synchronizing the whole function, as it gives us a lot
 * of extra time to do other useful work.
 */

// Simple pair class which is not thread-safe
class Pair {
	private int x;
	private int y;
	public Pair(int x, int y) {
		this.x = x;
		this.y = y;
	}
	public Pair() {
		this(0,0);
	}
	public void incrementX() {
		++x;
	}
	public void incrementY() {
		++y;
	}
	public int getX() {
		return x;
	}
	public int getY() {
		return y;
	}
	public class PairValuesNotEqualException extends RuntimeException {
		public PairValuesNotEqualException() {
			super("Pair values are not equal " + Pair.this);
		}
	}
	public void checkState() {
		if (x != y) {
			throw new PairValuesNotEqualException();
		}
	}
	public String toString() {
		return "X: " + x + "   Y: " + y;
	}
}

// This class created a synchronized List to which we add Pair objects.
// We also create threads later on which just keep on incrementing the "checkCounter" variable
abstract class PairManager {
	AtomicInteger checkCounter = new AtomicInteger(0);
	protected Pair p = new Pair();
	List<Pair> storage = Collections.synchronizedList(new ArrayList<Pair>());
	
	public synchronized Pair getPair() {
		return new Pair(p.getX(), p.getY());
	}
	
	public void store(Pair p) {
		storage.add(p);
		try {
			TimeUnit.MILLISECONDS.sleep(50);
		} catch (InterruptedException ignore) {}
	}
	
	public abstract void increment();
}


//PairManager1 synchronizes the whole function
class PairManager1 extends PairManager {
	public synchronized void increment() { //Note that the base class is not defined to be synchronized.
		p.incrementX();
		p.incrementY();
		store(p);
	}
}

//PairManager2 synchronizes the "this" object
class PairManager2 extends PairManager {
	public void increment() {
		Pair temp;
		synchronized (this) {
			p.incrementX();
			p.incrementY();
			temp = getPair();
		}
		store(temp);
	}
}

//Create a PairManipular which extends Runnable to create a run() method which will keep calling
// PairManager.increment() in an infinite loop.
class PairManipulator implements Runnable {
	PairManager pm;
	PairManipulator (PairManager pm) {
		this.pm = pm;
	}
	public void run() {
		while(true) {
			pm.increment();
		}
	}
	public String toString() {
		return "Pair: " + pm.getPair() + "   .....checkCounter: " + pm.checkCounter.get();
	}
}

//PairChecker class which also implements Runnable whose run() method increments "checkCounter"
//and also calls checkState()
class PairChecker implements Runnable {
	PairManager pm;
	public PairChecker(PairManager pm) {
		this.pm = pm;
	}
	public void run() {
		while(true) {
			pm.checkCounter.incrementAndGet();
			pm.getPair().checkState();
		}
	}
}

//This class created two PairManagers - PairManager1 & PairManager2
//Each PairManager is tied to a PairManipulator & PairChecker.
//Then we create 4 threads - two for PairManipulator and two for PairChecker
public class CriticalSection {
	public static void test(PairManager pman1, PairManager pman2) {
		ExecutorService exec = Executors.newCachedThreadPool();
		
		PairManipulator pm1 = new PairManipulator(pman1);
		PairManipulator pm2 = new PairManipulator(pman2);
		
		PairChecker pc1 = new PairChecker(pman1);
		PairChecker pc2 = new PairChecker(pman2);
		
		exec.execute(pm1);
		exec.execute(pm2);
		exec.execute(pc1);
		exec.execute(pc2);
		
		try {
			TimeUnit.MILLISECONDS.sleep(3000);
		}catch (InterruptedException e) {
			System.out.println(e);
		}
		System.out.println("pm1: " + pm1);
		System.out.println("pm2: " + pm2);
		System.exit(0);
	}
	
	public static void main(String[] args) {
		test(new PairManager1(), new PairManager2());
	}
}

/*
Please read SyncObject.java next
*/