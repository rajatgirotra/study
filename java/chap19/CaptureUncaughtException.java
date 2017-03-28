/*
 * Please read ExceptionThread.java first.
 * Demonstrate Thread.UncaughtExceptionHandler.
 */
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;

class CatchThreadException implements Thread.UncaughtExceptionHandler {
	public void uncaughtException(Thread t, Throwable e) {
		System.out.println("Unhandled Exception: " + e + " caught in " + t);		
	}
}

class ThreadExceptionFactory implements ThreadFactory {
	public Thread newThread(Runnable r) {
		Thread t = new Thread(r);
		t.setUncaughtExceptionHandler(new CatchThreadException());
		System.out.println("eh = " + t.getUncaughtExceptionHandler());
		return t;
	}
}


public class CaptureUncaughtException implements Runnable {
	public void run() {
		System.out.println("thread " + Thread.currentThread() + " throwing exception");
		throw new RuntimeException();
	}
	
	public static void main(String[] args) {
		ExecutorService exec = Executors.newCachedThreadPool(new ThreadExceptionFactory());
		exec.execute(new CaptureUncaughtException());
	}
}


/*
Very trivial code, I must say. 
Now if you know that you are going to use the same exception handler for all ur threads, you can create use
Thread.setDefaultUncaughtExceptionHandler() function to set the exception handler.

The JVM will first look for a specific Exception handler; if it is not able to find one, it will use the 
defaultExceptionHandler.

Next we'll see how to access shared resources in JAVA safely.
Please read IntGenerator.java next

*/