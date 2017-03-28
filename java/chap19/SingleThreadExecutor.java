/*
 * Please read FixedThreadPool.java first.
 */
import java.util.concurrent.*;
public class SingleThreadExecutor {
	public static void main(String[] args) {
		ExecutorService exec =
			Executors.newSingleThreadExecutor();
		for(int i = 0; i < 5; i++)
			exec.execute(new LiftOff());
		exec.shutdown(); //You should never forget to call this.
	}
}

/*
Please read Must_Read_2.txt next
*/