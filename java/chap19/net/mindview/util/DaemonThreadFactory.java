/*
 * Please read SimpleDaemons.java first
 * We create a Daemon Factory whose newThread() function returns a daemon thread.
 */
package net.mindview.util;
import java.util.concurrent.ThreadFactory;

public class DaemonThreadFactory implements ThreadFactory {
	public Thread newThread(Runnable r) {
		Thread t = new Thread(r);
		t.setDaemon(true);
		return t;
	}
}

/*
Please read DaemonFromFactory.java next
*/
