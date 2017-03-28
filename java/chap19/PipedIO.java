import java.io.IOException;
import java.io.PipedReader;
import java.io.PipedWriter;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/*
 * Please read ToastOMatic.java first.
 * You can also use PipedReader and PipedWriter classes to synchronize two tasks. You can think of the communication
 * channel as a Pipe. One task will read to it and the other task will write to the Pipe.
 * Please note that BlockingQueue is easier to use. But PipedReader and PipedWriter were part of JAVA library from the very
 * beginning.
 */

//class to write to the Piped - Uses PipedWriter
class Sender implements Runnable {
	private PipedWriter pw = new PipedWriter();
	private Random rand = new Random(47);
	public PipedWriter getPipedWriter() {
		return pw;
	}
	public void run() {
		try {
			while(true) {
				for(char c = 'A'; c <= 'z'; ++c) {
					pw.write(c);
					TimeUnit.MILLISECONDS.sleep(rand.nextInt(500));
				}
			}
		} catch (IOException e) {
			System.out.println("IOException in Sender: " + e);
		} catch(InterruptedException e) {
			System.out.println("Sender interrupted");
		}
		System.out.println("Finished Sending to Pipe");
	}
}

//class to read from the Pipe - Uses PipedReader
class Receiver implements Runnable {
	private PipedReader pr;
	public Receiver(Sender s) throws IOException {
		pr = new PipedReader(s.getPipedWriter());
	}
	public void run() {
		try {
			while(!Thread.interrupted()) {
				System.out.println("Read: " + (char)pr.read());
			}
		}catch (IOException e) {
			System.out.println("IOException in Receiver: " + e);
		}
		System.out.println("Finishing reading from Pipe");
	}
}

public class PipedIO {
	public static void main(String[] args) throws Exception {
		Sender s = new Sender();
		Receiver r = new Receiver(s);
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(s);
		exec.execute(r);
		
		//Shutdown after a few seconds.
		TimeUnit.SECONDS.sleep(4);
		exec.shutdownNow();
	}
}

/*
An important difference between a PipedReader and normal I/O is seen when shutdownNow() is called—the PipedReader is 
interruptible, whereas if you changed, for example, the in.read() call to System.in.read(), the interrupt() would fail to 
break out of the read( ) call.

Please read Chopstick.java next
*/