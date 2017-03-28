/*
 * Please read BasicThreads.java first
 * In this program we create more such threads. Simple and trivial.
 */
public class MoreBasicThreads {
	public static void main(String[] args) {
		for (int i = 0; i < 5; ++i) {
			new Thread(new LiftOff()).start();
		}
		System.out.println("Waiting for LiftOff");
	}
}

/*
Did you note something here:
The code creates thread objects but does not its references anywhere. So doesn't this make them ideal objects to be garbage collected.
The answer is NO: beacuse the thread objects register themselves internally somewhere in the JAVA code, so these are not garbage 
collected and they run to completion.

The Thread class also has a run method. This run method just calls the run() method of the Runnable object assigned 
to this Thread in a synchronous way; i.e. in the same thread. It is just like any other function call.

You creating a new Thread just to call its run() method is needlessly expensive and should be avoided. 
You can either call the run() method of the Runnable object directly or create a new Thread() & call its start method
to execute code in a separate thread.

If the thread was not constructed using a Runnable object, then this function does nothing and simply returns.
So you can also extend the Thread class and override the run() method to create and execute a new thread.

Please read Must_Read_1.txt next
*/