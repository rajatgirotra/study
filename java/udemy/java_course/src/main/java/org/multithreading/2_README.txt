Every java object has an implicit lock or monitor object. We can use this monitor object to synchronize critical sections of the code.

java provides a synchronized keyword which is used for mutual exclusion. the synchronized keyword can be applied to a method
or to a block. Example

class MyCriticalData {
   public synchronized void workOnData() {
      // the synchronized keyword automatically acquires the monitor of the "this" object.
      /*
      this means that if a thread enters a synchronized method on object1,
       1) no other thread can enter any synchronized method of that class using the same object1.
       2) another object2 can enter any synchronized method of that class
       3) object1 can safely call another synchronized method of that class on the same thread.
       */
   }
}

Also, the Class object of an object has a monitor object, which is used to synchronize the static methods of a class.

Synchronizing a block of code
=============================
SomeClass someObject; // instance member of a class.
public void foo() {
   synchronized(someObject) {
       // Critical Section
   }
}

Caveat
======
public void foo() {
    SomeClass someObject = null;
    switch(someExpression) {
       case "Thread 1 reaches here": someObject = new SomeObject();
       case "Thread 2 reaches here": someObject = new SomeObject();
    }

    synchronized(someObject) {
       // Oops. someObject is different for both threads. So both threads will execute code here concurrently.
    }
}

public void foo() {
    String foo = "foo";
    synchronized(foo) {
       // This is OK. because String are interned in Java, foo will point to the same reference in all threads.
       // so synchronized will work here correctly.
    }
}

Drawbacks of using synchronized
===============================
1) It can not be interrupted. If lock/monitor is unavailable, the thread will forever hang.
2) There is nothing like tryLock() available or nothing like timedLock() available.
3) synchronized locking is not fair. If several threads are blocked and the monitor becomes available,
any thread can acquire it. Adding fair-ness also adds runtime cost to synchronization.

So to overcome these issues we can use lock object from the java.util.concurrent package called ReentrantLock.
1) this lock has tryLock()
2) has tryLock(timeout)
3) can be fair if constructed by passing "true" as first argument.
4) can get hold count. i.e. how many times lock() has been called. Equal number of unlock() calls will release the lock.
5) and other functions too..

We will use it shortly.

But first we will write a simple Message class with two synchronized methods read() and write().
read() and write() strictly consume and strictly produce a single String object alternately. When read() reads "Finished",
 it means end of producing more Strings and the program can terminate.

Please read Message.java next
