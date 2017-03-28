import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read SyncObject.java first
 * Each thread can have its own local storage. What this means is that if multiple thread are sharing
 * a variable x in Object o, then each thread can have its own copy of variable x. So this will ensure
 * that there is no sharing of resources, hence you dont need to synchronize any of the functions.
 * 
 * For this we make use of the java.lang.ThreadLocal<T> class.
 */

class Accessor implements Runnable {
	private int id;
	Accessor(int idn) {
		id = idn;
	}
	public void run() {
		while(!Thread.currentThread().isInterrupted()) {
			ThreadLocalVariableHolder.increment();
			System.out.println(this);
			Thread.yield();
		}
	}

	public String toString() {
		return "#" + id + ": " + ThreadLocalVariableHolder.get();
	}
}
public class ThreadLocalVariableHolder {
	//ThreadLocal variables are normally created as static.
	private static ThreadLocal<Integer> intValue = new ThreadLocal<Integer>() {
		private Random rand = new Random(47);
		
		@Override
		protected synchronized Integer initialValue() {
			return rand.nextInt(10000);
		}
	};

	public static void increment() {
		intValue.set(intValue.get() + 1);
	}

	public static Integer get() {
		return intValue.get();
	}

	public static void main(String[] args) throws Exception {
		ExecutorService exec = Executors.newCachedThreadPool();
		for(int i = 0; i < 5; i++)
			exec.execute(new Accessor(i));
		TimeUnit.SECONDS.sleep(3); // Run for a while
		exec.shutdownNow(); // All Accessors will quit
	}		
}

/*
The ThreadLocal class has an initialValue() method that gets invoked only once; this happens on the first
call to the ThreadLocal.get() method. If you call the ThreadLocal.set() method before the ThreadLocal.get()
method, it will never invoke the initialValue() method.

If you want to assign an initialValue to your ThreadLocal variable, you must subclass it and override the
initialValue() method; typically using an anonymous inner class; as is done here.

Please read OrnamentalGarden.java next
*/