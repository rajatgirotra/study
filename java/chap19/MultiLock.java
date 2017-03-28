/*
 * Please read NIOInterruption.java first
 * You already know that if task is inside a synchronized method, then no other task can enter the synchronized method
 * on the same object. But a task which is inside a synchronized method can enter other synchronized methods on the same 
 * object.
 */
public class MultiLock {
	public synchronized void f1(int count) {
		System.out.println("f1() called with " + count);
		--count;
		if(count > 0)
		f2(count);
	}
	public synchronized void f2(int count) {
		System.out.println("f2() called with " + count);
		--count;
		if(count > 0)
		f1(count);
	}
	public static void main(String[] args) {
		final MultiLock ml = new MultiLock();
		new Thread() {
			public void run() {
				ml.f1(10);
			}
		}.start();		
	}
}

/*
 *  This makes sense because the lock is already acquired by the task.
 *  Please read Interrupting2.java
 */
