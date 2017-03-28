/*
 * Please read CallableDemo.java first
 * You might be knowing that adding a sleep() to your task can modify the output. This is because you are actually blocking the 
 * execution of the task for some time. so the Thread Scheduler will do a context switch.
 */
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Sleeping extends LiftOff {	
	public void run() {
		while(countDown-- > 0) {
			System.out.print(status());
			try {
				TimeUnit.MILLISECONDS.sleep(100);				
			} catch (InterruptedException e) {
				System.out.println(e);
			}
		}
	}
	
	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool();
		for(int i = 0; i < 5; ++i) {
			exec.execute(new Sleeping());
		}
		exec.shutdown(); //You should not forget to call this.
	}
}

/*
The most important learning from this task should be:
The call to sleep() can throw an InterruptedException, and you can see that this is caught in run(). 
Because exceptions won’t propagate across threads back to main(), you must locally handle any exceptions 
that arise within a task.

Please read SimplePriorities.java next
*/