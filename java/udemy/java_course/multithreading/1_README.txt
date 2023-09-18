Ways to create threads in java.

1st Way
========
Just extend from Thread and override the run method. Later call the start() function on your derived class. Note that calling the run() function will 
not start a new thread. calling thread's start() function will install all the machinery for creating and starting a new thread.

class CounterThread extends Thread {
    @Override
    public void run() {
        System.out.println("new thread starting..");
    }
}
CounterThread ct = new CounterThread();
ct.start();

2nd Way
========
Just implement the Runnable interface and override the run method. Later need to create a Thread object and pass this class as a Runnable. Then as before
call start() function on the thread object.

class CounterThread implements Runnable {
    @Override
    public void run() {
        System.out.println("new thread starting..");
    }
}
CounterThread ct = new CounterThread();
Thread someObj = new Thread(ct);
ct.start();

The 1st way is good enough, if you are sure your class doesnt need to extend any other class except Thread. Otherwise it is good to just implement Runnable.