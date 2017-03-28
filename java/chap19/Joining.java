/*
 * Please read SelfManaged.java first
 * One thread may call join( ) on another thread to wait for the second thread to complete before proceeding. If a thread 
 * calls t.join( ) on another thread t, then the calling thread is suspended until the target thread t finishes 
 * (when t.isAlive( ) is false).
 * You may also call join( ) with a timeout argument (in either milliseconds or milliseconds and nanoseconds) so that if 
 * the target thread doesn’t finish in that period of time, the call to join( ) returns anyway.
 * The call to join( ) may be aborted by calling interrupt( ) on the calling thread, so a try-catch clause is required.
 */

class Sleeper extends Thread {
	private int duration;

	public Sleeper(String name, int sleepTime) {
		super(name);
		duration = sleepTime;
		start();
	}
	public void run() {
		try {
			sleep(duration); // -->> Thread.sleep(long milliseconds);
		}catch(InterruptedException e) {
			System.out.println(getName() + " was interrupted!!  isInterrupted() = " + isInterrupted());
			return;
		}
		System.out.println(getName() + " has awakened");
	}
}

class Joiner extends Thread {
	private Sleeper sleeper;

	public Joiner(String name, Sleeper sleeper) {
		super(name);
		this.sleeper = sleeper;
		start();
	}
	public void run() {
		try {
			sleeper.join();
		} catch (InterruptedException e) {			
			System.out.println(getName() + " was interrupted!!  isInterrupted() = " + isInterrupted());
		}
		System.out.println(getName() + " join completed");
	}
}
public class Joining {
	public static void main(String[] args) {
		Sleeper sleepy = new Sleeper("Sleepy", 3000),
				grumpy = new Sleeper("Grumpy", 3000);
		
		Joiner	dopey = new Joiner("Dopey", sleepy),
				doc = new Joiner("Doc", grumpy);
		
		grumpy.interrupt();
	}
}

/*
	2 Things to note here.

When another thread calls interrupt() on this thread, a flag is set to indicate that the thread has been interrupted. 
However, this flag is cleared when the exception is caught, so the result will always be false inside the catch clause. 
The flag is used for other situations where a thread may examine its interrupted state apart from the exception.

A Joiner is a task that waits for a Sleeper to wake up by calling join() on the Sleeper object. In main(), each Sleeper 
has a Joiner, and you can see in the output that if the Sleeper either is interrupted or ends normally, the Joiner completes 
in conjunction with the Sleeper.

Please read ResponsiveUI.java next
*/