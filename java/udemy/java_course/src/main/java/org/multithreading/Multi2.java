package org.multithreading;

import static org.multithreading.ThreadColors.*;

/*
Every Thread has an interrupt status. You can fetch it using:
interrupted() or
isInterrupted()
both return boolean true/false but interrupted() further also clears the interrupt state. So that if two subsequent calls to
interrupted() are made, the second one will always return false.

How to set the interrupt() state?? You can not explicitly set to true/false. You can only interrupt a thread by calling its
interrupt() method and the state is set/unset according to some rules:

1) If thread was in a wait(), or join() or sleep() call(or any variant of these calls), the interrupt state is unset and InterruptedException is raised.
2) If thread was blocked in some I/O operation on some interruptible channel, the channel is closed, the interrupt state is set and ClosedByInterruptException is raised.
3) If thread was blocked in some Selector, then also the interrupt state is set, and the thread will return from the Selector operation
4) For everything else, the interrupt state is set.

Thread.join() will cause the current thread to block until the thread on which join() is called is alive.
 */
public class Multi2 {
    public static void main(String[] args) {
        System.out.println(ANSI_GREEN + "Hello from thread: " + Thread.currentThread().getName());

        // creating AnotherThread
        Thread anotherThread = new AnotherThread("Another Thread");
        anotherThread.start();

        try {
            anotherThread.start();
        } catch(IllegalThreadStateException e) {
            System.out.println(ANSI_GREEN + "Exception caught in trying to start AnotherThread twice");
            e.printStackTrace();
        }

        // creating an anonymous thread and start immediately
        new Thread() {
            @Override
            public void run() {
                System.out.println(ANSI_CYAN + "This is printing from inside an anonymous Thread class. thread name is: "
                        + Thread.currentThread().getName());
            }
        }.start();

        var runnableThread = new Thread(new RunnableThread());
        runnableThread.start();

        // creating an anonymous Runnable thread.
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                System.out.println(ANSI_CYAN + "This is printing from inside an anonymous Runnable class. thread name is: "
                        + Thread.currentThread().getName());
                try {
                    System.out.println(ANSI_CYAN + "Inside anonymous Runnable class waiting on Another thread: "
                            + Thread.currentThread().getName());
                    anotherThread.join(4000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                System.out.println(ANSI_CYAN + "Inside anonymous Runnable class wait over on Another thread: "
                        + Thread.currentThread().getName() + " is another thread still alive: " + anotherThread.isAlive());
            }
        };
        var runnableThread2 = new Thread(runnable);
        runnableThread2.start();


    }
}

/* Please read CountdownMain.java next */