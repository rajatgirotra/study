/*
 * Please read EvenChecker.java first
 */
public class EvenGenerator extends IntGenerator {
	private int currentValue = 0;
	public int next() {
	//public synchronized int next() { // uncomment this after reading the comments below.
		++currentValue; // danger is here
		Thread.yield(); // This is added to increase the likelihood of a different thread being scheduled here.
		++currentValue;
		return currentValue;
	}
	
	public static void main(String[] args) {
		EvenChecker.test(new EvenGenerator());
	}
}

/*
It’s possible for one task to call next() after another task has performed the first increment of currentValue but 
not the second (at the place in the code commented "Danger point here!"). This puts the value into an "incorrect" 
state leading to a retrieval of odd value.

To prevent this kind of collosion, we must use some kind of a locking mechanism, where we acquire some a lock 
before entering the method, and release it on exit. What this means is that we must serialize access to the shared
resource. This is also referred to as mutual exclusion. 
JAVA provides built in support to perform this kind of locking using the synchronized keyword. To use this keyword,
you wrap the resource which is mostly an object inside a method and declare that method as synchronized.

To control access to a shared resource, you first put it inside an object. Then any method that uses the resource can 
be made synchronized. If a task is in a call to one of the synchronized methods, all other tasks are
blocked from entering any of the synchronized methods of that object until the first task returns from its call.

In production code, you’ve already seen that you should make the data elements of a class private and access that 
memory only through methods. You can prevent collisions by declaring those methods synchronized, like this:

synchronized void f() {  ...  }
synchronized void g() {  ...  }

All objects automatically contain a single lock (also referred to as a monitor). When you call any synchronized method, 
that object is locked and no other synchronized method of that object can be called until the first one finishes and 
releases the lock. For the preceding methods, if f() is called for an object by one task, a different task cannot call f() 
or g() for the same object until f() is completed and releases the lock. Thus, there is a single lock that is shared by all 
the synchronized methods of a particular object, and this lock can be used to prevent object memory from being written by more 
than one task at a time.

Note that it’s especially important to make fields private when working with concurrency; otherwise the synchronized keyword cannot 
prevent another task from accessing a field directly, and thus producing collisions.

There’s also a single lock per class (as part of the Class object for the class), so that synchronized static methods can lock each 
other out from simultaneous access of static data on a class-wide basis.

Remember:
Every method that accesses a critical shared resource must be synchronized or it won’t work right.

You can add the synchronized keyword to the next() method and see the difference in the result.

Please read MutexEvenGenerator.java next
*/