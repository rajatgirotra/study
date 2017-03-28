/*
 * Please read Must_Read_1.txt first
 * This program shows how to use the Executor interface to run tasks instead of creating the Thread object.
 * This is also the preferred way in JAVA 5/6.
 */
import java.util.concurrent.*;
public class CachedThreadPool {
	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool();
		for(int i = 0; i < 5; ++i) {
			exec.execute(new LiftOff());
		}
		exec.shutdown(); //You should never forget to call this.
	}
}

/*
exec.shutdown()
Initiates an orderly shutdown in which previously submitted tasks are executed, but no new tasks will be accepted. Invocation has 
no additional effect if already shut down. 

Please read FixedThreadPool.java next
 */
