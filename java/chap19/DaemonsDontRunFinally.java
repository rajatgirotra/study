/*
 * Please read Daemons.java first
 * A good point to remember is that a daemon thread will not run the finally clause.
 * Daemons are terminated "abruptly" when the last of the non-daemons terminates. So as soon as main() exits, the JVM 
 * shuts down all the daemons immediately, without any of the formalities you might have come to expect. Because you 
 * cannot shut daemons down in a nice fashion, they are rarely a good idea.
 */
import java.util.concurrent.TimeUnit;

class ADaemon implements Runnable {
	public void run() {
		try {
			System.out.println("Daemon thread started..!!");
			TimeUnit.MILLISECONDS.sleep(1000);
		}catch (Exception e) {
			System.out.println("Exception caught: " + e);
		}finally {
			System.out.println("In finally clause");
		}
	}
}
public class DaemonsDontRunFinally {
	public static void main(String[] args) throws Exception {
		Thread t = new Thread(new ADaemon());
		//t.setDaemon(true);
		t.start();
		TimeUnit.MILLISECONDS.sleep(100);
	}
}

/*
Please read SimpleThread.java next
*/