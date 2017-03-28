/*
 * Please read ThreadInterrupting.java next
 * New IO classes handle interruption of I/O in a more civilized way.
 * Blocked NIO channels automatically respond to interrupts.
 */
import java.net.*;
import java.nio.*;
import java.nio.channels.*;
import java.util.concurrent.*;
import java.io.*;

class NIOBlocked implements Runnable {
	private final SocketChannel sc;
	public NIOBlocked(SocketChannel sc) { this.sc = sc; }
	public void run() {
		try {
			System.out.println("Waiting for read() in " + this);
			sc.read(ByteBuffer.allocate(1));
		} catch(ClosedByInterruptException e) {
			System.out.println("ClosedByInterruptException");
		} catch(AsynchronousCloseException e) {
			System.out.println("AsynchronousCloseException");
		} catch(IOException e) {
			throw new RuntimeException(e);
		}
		System.out.println("Exiting NIOBlocked.run() " + this);
	}
}
public class NIOInterruption {
	public static void main(String[] args) throws Exception {
		ExecutorService exec = Executors.newCachedThreadPool();

		ServerSocket server = new ServerSocket(8080);
		InetSocketAddress isa =	new InetSocketAddress("localhost", 8080);

		SocketChannel sc1 = SocketChannel.open(isa);
		SocketChannel sc2 = SocketChannel.open(isa);

		Future<?> f = exec.submit(new NIOBlocked(sc1));
		exec.execute(new NIOBlocked(sc2));

		exec.shutdown(); // Just stops accepting any new thread execution requests and executes any threads that are
		//already submitted.
		TimeUnit.SECONDS.sleep(1);

		// Produce an interrupt via cancel:
		f.cancel(true); //calls Thread.interrupt() which raise a ClosedByInterruptException.
		//If another thread interrupts the current thread while the read operation is in progress, thereby closing the channel
		//and setting the current thread's interrupt status

		TimeUnit.SECONDS.sleep(1);
		// Release the block by closing the channel:
		sc2.close(); // raises an AsynchronousCloseException.
		//If another thread closes this channel while the read operation is in progress 
	}
}

/*
Please read MultiLock.java next 
*/