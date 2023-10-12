package org.multithreading;

/* we will create two simple threads that countdown from 10 to 1.
and observe the behavior when the share or do not share the same object that maintains the countdown value.
 */
import static org.multithreading.ThreadColors.*;

public class CountdownMain extends Thread {
    public static void main(String[] args) {
        Countdown cd = new Countdown();

        Thread countdownThread1 = new CountdownThread(cd);
        countdownThread1.setName("Thread 1");

        Thread countdownThread2 = new CountdownThread(cd);
        countdownThread2.setName("Thread 2");

        countdownThread1.start();
        countdownThread2.start();
    }
}

class Countdown {
    private int i;

    public void doCountdown() {
        String color;
        switch (Thread.currentThread().getName()) {
            case "Thread 1":
                color = ANSI_CYAN;
                break;
            case "Thread 2":
                color = ANSI_PURPLE;
                break;
            default:
                color = ANSI_RESET;
        }

        // the variable i is local variable on each thread's thread stack. So no thread interference will happen and both will be able to countdown from 10 to 1
         for(int i = 10; i > 0; --i) {

        // the variable i is a member variable of the shared Countdown object on the heap, so it is shared without any explicit synchronization. So thread interference will occur
        // causing race conditions. the output totally depends on how the OS schedules the two threads. A thread may be suspended at any of the suspension points.
//        for(i = 10; i > 0; --i) {
            System.out.println(color + Thread.currentThread().getName() + ", i = " + i);
        }
    }
}


class CountdownThread extends Thread {
    private final Countdown countdown;

    public CountdownThread(Countdown countdown) {
        super();
        this.countdown = countdown;
    }

    @Override
    public void run() {
        countdown.doCountdown();
    }
}
/*
Please read 2_README.txt next
 */