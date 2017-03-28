/*
 * Please read LiftOff.java first
 * A simple way to call run(). The run() method here is not called by a separate thread.
 * What I am trying to say is that implementing Runnable does not give you any innate threading capabilities. To exhibit threading
 * behavior, you must first explicitly attach a task to a thread.
 */
public class MainThread {
	public static void main(String[] args) {
		LiftOff lift = new LiftOff(15);
		lift.run();
	}
}

/*
Please read BasicThreads.java next
*/