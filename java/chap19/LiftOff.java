import java.util.concurrent.TimeUnit;

/*
 * This is the first program in this chapter.
 * OK, in JAVA threading a source program is broken up into smaller tasks. Each task needs a thread to execute which it can get
 * by implementing the Runnable interface. Any class that implements Runnable must provide a definition for the "public void run()" 
 * method of Runnable. This method is called by the JVM when the task first begins executing.
 * 
 * JVM has a Thread scheduler at its core. The static Thread.yield() function tells the JVM that I am finished doing the important
 * parts of my task and that it is a good time to preempt me. Remember, that this call is optional, so you may or may not add that line
 * to your task. 
 */
public class LiftOff implements Runnable {
	private static int taskCount = 0;
	protected int countDown = 10;
	private int id = taskCount++;

	public LiftOff() {}
	public LiftOff(int countDown) {
		this.countDown = countDown;
	}
	public String status() {
		return "#" + id + "(" +
		(countDown > 0 ? countDown : "Liftoff!") + "), ";
	}
	public void run() {
		while(countDown-- > 0) {
			System.out.print(status());
			Thread.yield();
		}
	}
}

/*
Please read MainThread.java next
*/