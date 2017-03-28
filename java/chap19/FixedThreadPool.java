/*
 * Please read CachedThreadPool() 
 * You already know all this from Must_Read_1.txt
 */

import java.util.concurrent.*;

public class FixedThreadPool {
	public static void main(String[] args) {
		// Constructor argument is number of threads:
		ExecutorService exec = Executors.newFixedThreadPool(5);
		for(int i = 0; i < 5; i++)
			exec.execute(new LiftOff());
		exec.shutdown(); //You should never forget to call this.
	}
}

/*
Please read SingleThreadExecutor.java next
*/