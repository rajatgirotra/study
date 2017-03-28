/*
 * Please read CriticalSection.java first
 * Here we show that it is possible to synchronize on object other than "this"
 * In such a case two or more tasks can enter an object as shown below.
 */

class DualSync {
	private Object syncObject = new Object();
	public synchronized void f() { //synchronized on this.
		for (int i = 0; i < 5; ++i) {
			System.out.println("f()");
			Thread.yield();			
		}
	}
	
	public void g() {
		synchronized (syncObject) {	//synchronized on syncObject
			for(int i =0; i < 5; ++i) {
				System.out.println("g()");
				Thread.yield();				
			}
		}
	}
}

public class SyncObject {
	public static void main(String[] args) {
		final DualSync ds = new DualSync();
		new Thread() {
			public void run() {
				ds.f();
			}
		}.start();
		ds.g();		
	}

}

/*
Please read ThreadLocalVariableHolder.java next
*/