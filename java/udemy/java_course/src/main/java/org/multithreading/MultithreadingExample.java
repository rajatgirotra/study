package org.multithreading;

class MultiThread extends Thread {
    @Override
    public void run() {
        for(int i = 1; i <= 5; ++i) {
            System.out.println(i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class MultiThread2 implements Runnable {
    @Override
    public void run() {
        for(int i = 1; i <= 5; ++i) {
            System.out.println(i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class MultithreadingExample {
    public static void main(String[] args) {
        MultiThread mt1 = new MultiThread();
        MultiThread mt2 = new MultiThread();
        mt1.start();
        mt2.start();

        //System.out.println();
        MultiThread2 mt3 = new MultiThread2();
        MultiThread2 mt4 = new MultiThread2();
        Thread t1 = new Thread(mt3);
        Thread t2 = new Thread(mt4);
        t1.start();
        t2.start();
    }
}
