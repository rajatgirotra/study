import java.util.concurrent.TimeUnit;

/*
 * Please read DaemonsDontRunFinally.java first.
 * Another variation to using Runnable is to directly extend the thread class.
 * Earlier we use to pass a reference to a Runnable to the Thread c'tor.
 * The Thread class has a default run() method which does nothing but only call
 * the run() method on the Runnable reference passed to Thread. but when you provide your
 * own Thread implementation, you should override the default run() method as there is no Runnable. 
 */
public class SimpleThread extends Thread {
	private static int threadCount = 0;
	private int countDown = 5;
	
	public SimpleThread() {
		super(Integer.toString(++threadCount));
		start(); // --> This will start Thread.run() method in a new Thread.
	}
	
	public String toString() {
		return "#" + getName() + " : " + " ( " + countDown + " ) ";
	}
	
	public void run() {
		while(true) {
			System.out.println(this);
			Thread.yield();
			if(--countDown == 0)
				return;
		}
	}
	
	public static void main(String[] args) {
		for(int i = 0; i < 8; ++i) {
			new SimpleThread();			
		}
	}
}

/*
Please read SelfManaged.java next
*/