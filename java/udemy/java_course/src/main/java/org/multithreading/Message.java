package org.multithreading;

import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Message {
    private String message; // produce will set this and consumer will get this.
    private boolean empty = true; // used by consumer and producer to signal when item is available/unavailable

    public synchronized String read() {
        while(empty) {
            // nothing to read(). just wait.
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("read() interrupted");
            }
        }
        // if we reach here, empty is false and message is ready for consumption.
        empty = true;
        notifyAll(); // will wake up the write() thread. However that thread still can't proceed as the write() method
        // is synchronized. It can only update "message" member variable after this function ends and monitor/lock is available again.
        return message;
    }

    public synchronized void write(String message) {
        while(!empty) {
            // cannot write(). waiting for consumer to consume first
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("write() interrupted");
            }
        }
        // if we reach here, empty is true and message is assumed consumed.
        empty = false;
        this.message = message;
        notifyAll(); // will wake up the read() thread.
        return;
    }

    public static void main(String[] args) {
        Message obj = new Message();
        try {
            ExecutorService es = Executors.newFixedThreadPool(2);
            es.execute(new StrictConsumer(obj));
            es.execute(new StrictProducer(obj));
            es.shutdown();
        } catch(Exception e) {

        }
    }
}

class StrictConsumer implements Runnable {
    private Message message;
    private static final Random rand = new Random();
    public StrictConsumer(Message message) {
        this.message = message;
    }

    @Override
    public void run() {
        String buffer = null;
        for(buffer = message.read(); !buffer.equals("Finished"); buffer = message.read()) {
            System.out.println(buffer);
            try {
                Thread.sleep(rand.nextInt(2000));
            } catch(InterruptedException e) {
                System.out.println("StrictConsumer interrupted");
            }
        }
    }
}

class StrictProducer implements Runnable {
    private Message message;
    private static final Random rand = new Random();

    public StrictProducer(Message message) {
        this.message = message;
    }

    @Override
    public void run() {
        String[] buffer = {"Humpty Dumpty sat on a wall!",
                "Humpty Dumpty had a great fall!",
                "All ths kings horses and all the kings men,",
                "Could not put Humpty together again!"
        };

        for (String s : buffer) {
            try {
                this.message.write(s);
                Thread.sleep(rand.nextInt(2000)); // wait for max 2 secs.
            } catch (InterruptedException e) {
                System.out.println("StrictProducer interrupted");
            }
        }

        message.write("Finished");
    }
}

/*
Please read ProducerConsumer.java next.
 */