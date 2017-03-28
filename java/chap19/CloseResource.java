import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read Interrupting.java first
 */
public class CloseResource {
	public static void main(String[] args) throws UnknownHostException, IOException, InterruptedException {
		ExecutorService exec = Executors.newCachedThreadPool();
		InputStream socketInput = new Socket("localhost", 7081).getInputStream();
		
		exec.execute(new IOBlocked(socketInput));
		exec.execute(new IOBlocked(System.in));
		TimeUnit.SECONDS.sleep(2);
		
		System.out.println("Shutting down all threads");
		exec.shutdownNow();
		TimeUnit.SECONDS.sleep(2);
		
		System.out.println("Closing  " + socketInput.getClass().getName());
		socketInput.close(); // Closing the socket resource releases the blocked thread.
		
		TimeUnit.SECONDS.sleep(2);
		System.out.println("Closing  " + System.in.getClass().getName());
		System.in.close(); // But it is the not the case here, this is weird!!! You have to enter something on the console
		//and hit <return> for the program to terminate
	}
}

/*
A very important word about exec.shutdownNow()
---------------------------------------------

exec.shutdown() will do the following:

1] Halt all the active tasks.
2] Any tasks which were waiting or blocked will also be halted
3] Returns a list of Runnable which were never executed. 

Actually implementations of exec.shutdownNow() will call Thread.interrupt() for all the threads.
This will have no impact on non-interruptible blocking calls such as synchronized waiting or I/O blocking calls

So exec.shutdownNow() does not guarantee to shutdown all tasks. It just makes a best-effort to do so.

Please read ThreadInterrupting.java next

*/