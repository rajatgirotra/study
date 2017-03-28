/*
 * The traditional way of running a task is to hand your Runnable object to the Thread c'tor and then to call start() on it.
 * This is shown below:
 */
public class BasicThreads {
	public static void main(String[] args) {
		Thread t = new Thread(new LiftOff());
		
		//See the difference between output with Thread.start() and Thread.run()
		//Thread.start() invokes the JVM thread schedular which calls the run() method in 
		//the underlying Runnable object in a separate thread. So this function
		//returns immediately.
		//t.start(); 
		
		//Thread.run() also calls the run() method of the underlying Runnable
		//but in the same thread. So Runnable.run() executes in the same thread.
		t.run();
		System.out.println("Waiting for LiftOff");
	}
}

/*
A Thread constructor only needs a Runnable object. Calling a Thread object’s start() will perform the necessary initialization for 
the thread and then call that Runnable’s run() method to start the task in the new thread.
The start() method returns immediately, that's why the "Waiting for LiftOff" string is printed out first.

 Please read MoreBasicThreads.java next
*/