/*
 * Please read SimpleThread.java first
 * Another approach to create tasks is to implement the Runnable interface and also hold a Thread object within 
 * your class. this is called as the self managed idiom.
 */
public class SelfManaged implements Runnable {
	private static int threadCount = 0;
	private int countDown = 5;
	private Thread t = new Thread(this);
	
	SelfManaged() {
		t.start();
	}
	public void run() {
		while(true) {
			System.out.println(Thread.currentThread().getName() + " : " + "( " + countDown + " ) ");
			if(--countDown == 0) return;
		}
	}
	
	public static void main(String[] args) {
		for(int i = 0; i < 5; ++i) {
			new SelfManaged();
		}
	}
}

/* 
 * There are numerous other ways in which you can create a Thread and bind a task to it. Remember, there is a clear
 * distinction between Threads and Tasks in JAVA. The Thread class does not do anything by itself. It just drives
 * the task that is assigned to it. Please refer to Thinking in JAVA 4th Edition (page 816 - 818) for more.
 * 
 * Please read Joining.java next
 */ 
