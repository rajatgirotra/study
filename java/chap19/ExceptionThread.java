/*
 * Please read ResponsiveUI.java first.
 * An exception cannot be caught once it has escaped past its run() method. Such exceptions propagate out to the console.
 * To capture such exceptions, you can make use of Executors.
 * The program below displays one such unhandled exception.
 * 
 */
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ExceptionThread implements Runnable {
	public void run() {
		throw new RuntimeException();
	}
	public static void main(String[] args) {
		//try {
			ExecutorService exec = Executors.newCachedThreadPool();
			exec.execute(new ExceptionThread());	
		//}catch(Exception e) {
		//	System.out.println(e);
		//}		
	}
}

/*
Even if you put the body of the main in a try-catch block, it wont be handled.
Try to uncomment the try-catch block above and you'll see no change in the output.

You can make use of Thread.UncaughtExceptionHandler interface to catch such exceptions.
You can create a class that implements the above interface and then pass a reference of that class to the 
Thread.setUncaughtExceptionHandler() function. We create a new ThreadFactory in which we call Thread.setUncaughtExceptionHandler()
and then we attach that ThreadFactory to Executors.newCachedThreadPool().

Please read CaptureUncaughtException.java next
*/