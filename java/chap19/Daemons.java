/*
 * Please read DaemonsFromFactory.java first.
 * If you create a Daemon thread, then all threads created by this daemon thread will be automatically daemons.
 * The example below will demonstrate this.
 */
import java.util.concurrent.TimeUnit;

class Daemon implements Runnable {
	private Thread[] t = new Thread[10];
	public void run() {
		for(int i = 0; i < t.length; ++i) {
			t[i] = new Thread(new DaemonSpawn());
			t[i].start();
			System.out.println("DaemonSpawn " + i + " started");
		}
		for(int i = 0; i < t.length; ++i) {
			System.out.print("DaemonSpawn " + i + " is a ");
			if (t[i].isDaemon()) {
				System.out.println("Daemon");
			}else {
				System.out.println("Non Daemon");
			}			
		}
		while(true)
			Thread.yield();
	}
}

class DaemonSpawn implements Runnable {
	public void run() {
		while(true) {
			Thread.yield();
		}
	}
}
public class Daemons {
	public static void main(String[] args) throws InterruptedException {
		Thread t = new Thread(new Daemon());
		t.setDaemon(true);
		t.start();
		TimeUnit.MILLISECONDS.sleep(2000);
	}
}

/*
Please read DaemonsDontRunFinally.java next
*/